#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

class Checker {
public:
	bool exists()
	{
		std::vector<std::wstring> windowTitles = getAllWindows(); // Stores all active window titles in a wide-string vector
		for (const auto& title : windowTitles) { 
			if (checkTitle(title.c_str())) return true;
		}
		// Sorts through each "title" in the window title vector, similar to foreach
		// c_str checks if the "title" contains "Cheat Engine 7.5" through the pointer
		return false;
	}

private:
	static BOOL CALLBACK FilterTitles(HWND hwnd, LPARAM lParam) // Callback function that retrieves the window title
	{
		std::vector<std::wstring>& windowTitles = *reinterpret_cast<std::vector<std::wstring>*>(lParam); // Converts lparam (pointer) to a wide string

		wchar_t windowTitle[256];
		GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
		windowTitles.push_back(windowTitle); // Adds the converted lparam to the windowtitles vector

		return TRUE; // Continuing enumeration
	}

	std::vector<std::wstring> getAllWindows() /// Function that returns every active window title
	{ 
		std::vector<std::wstring> windowTitles;
		EnumWindows(FilterTitles, reinterpret_cast<LPARAM>(&windowTitles)); // I fucking hate this function
		// Ok so EnumWindows enumerates all active running windows	and reinterprets the lparam to the actual window titles vector (THANKS STACK OVERFLOW)
		return windowTitles;
	}

	bool checkTitle(const wchar_t* title)
	{
		const wchar_t* cheatEngine = L"Cheat Engine 7.5"; // Only works for 7.5 right now
		return (wcsstr(title, cheatEngine)); // Checks if the passed title matches the content of the cheatEngine ponter
	}
};

int main()
{
	Checker check;
	while (true) {
		if (check.exists())
			std::cout << "Cheat engine found" << std::endl;
		else
			std::cout << "Cannot find cheat engine" << std::endl;

		Sleep(3000);
	}

	return 0;
}
