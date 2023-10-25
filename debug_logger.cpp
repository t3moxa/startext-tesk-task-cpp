#include "debug_logger.h"
#include <fstream>
#include <iostream>
using namespace std;

struct Data {
    Data(int num, std::wstring text) {
        this->num = num;
        this->text = text;
    }
    int num;
    std::wstring text;
public:
    int getNum()
    {
        return this->num;
    }
    wstring getText()
    {
        return this->text;
    }
};

namespace stxDebug {
    wstring globalName;
    template<>
    struct GetDbgStringT<Data>
    {
        static std::wstring GetDbgString(Data Dat)
        {
            return L"{ class: 'Data', object: { num: " + stxUnicode::s2ws(to_string(Dat.getNum())) + L", text: '" + Dat.getText() + L"' } }";
        }
    };
    struct StdFileWriter
    {
        inline void operator()(const std::wstring& text)
        {
            ofstream debugFile;
            debugFile.open(globalName.c_str());
            debugFile << stxUnicode::ws2s(text) << endl;
            debugFile.close();
        }
    };
    stxDebug::DebugLogger<StdFileWriter> File(const wchar_t* name)
    {
        ofstream debugFile(name);
        stxDebug::globalName = std::wstring(name);
        return DebugLogger<StdFileWriter>();
    }
} // namespace stxDebug

int main(int argc, const char* argv[]) {
    std::setlocale(LC_ALL, "");

    cout << "stx C++ test task" << endl;

    stxDebug::Out() << L"wide text" << std::wstring(L" - std::wstring") << " - ascii text" << std::string(" - std::string");
    stxDebug::Err() << L"wide text" << std::wstring(L" - std::wstring") << " - ascii text" << std::string(" - std::string");

    // stx: task is to uncomment and revive this line
    stxDebug::File(L"Ä Ö Ü ß.log") << L"Dump of data: " << Data(55, L"stx data: Ä Ö Ü ß");

    return 0;
}