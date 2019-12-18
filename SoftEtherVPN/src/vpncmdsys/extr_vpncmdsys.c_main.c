#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int ExecProcess (char*,int*) ; 
 int* GetCommandLineW () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int MAX_SIZE ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VPNCMD_BOOTSTRAP_REG_KEYNAME ; 
 int /*<<< orphan*/  VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int ret_code ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  swprintf (int*,int,char*,char*,int*) ; 

int main(int argc, char *argv[])
{
	HKEY hKey;
	bool ok = false;
	char error[MAX_SIZE];
	wchar_t *current_args;
	bool flag = false;
	bool break_now = false;

	error[0] = 0;

	setlocale(LC_ALL, "");

	current_args = GetCommandLineW();

	// Remove the program name portion from the command line string
	while (true)
	{
		switch (*current_args)
		{
		case L'\"':
			if (flag == false)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;

		case L' ':
		case L'\t':
		case 0:
			if (flag == false)
			{
				break_now = true;
			}
			break;
		}
		if (break_now)
		{
			break;
		}
		current_args++;
	}

	while (true)
	{
		if (*current_args == L' ' || *current_args == L'\t')
		{
			current_args++;
		}
		else
		{
			break;
		}
	}

	strcpy(error, "VPN Command Line Tools is not Installed.\nPlease reinstall programs.");

	// Get the path of the vpncmd.exe from the registry
	if (RegOpenKey(HKEY_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, &hKey) == 0)
	{
		DWORD type = REG_SZ;
		DWORD size = 4096;
		char buf[4096];

		if (RegQueryValueEx(hKey, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH, NULL, &type, (LPBYTE)buf, &size) == 0)
		{
			wchar_t args[MAX_SIZE];

			swprintf(args, sizeof(args), L"\"%S\" %s", buf, current_args);
			if (ExecProcess(buf, args) == false)
			{
				//sprintf(error, "Failed to execute \"%S\".", buf);
			}
			else
			{
				ok = true;
			}
		}

		RegCloseKey(hKey);
	}

	if (ok == false)
	{
		printf("%s\n", error);
	}

	return ret_code;
}