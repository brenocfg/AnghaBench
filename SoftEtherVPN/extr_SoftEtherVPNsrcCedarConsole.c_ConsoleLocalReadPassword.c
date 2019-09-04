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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleWriteOutFile (int /*<<< orphan*/ *,char*,int) ; 
 char* CopyStr (char*) ; 
 scalar_t__ PasswordPrompt (char*,int) ; 
 int /*<<< orphan*/  UniPrint (char*,char*) ; 
 char* _UU (char*) ; 

char *ConsoleLocalReadPassword(CONSOLE *c, wchar_t *prompt)
{
	char tmp[64];
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}
	if (prompt == NULL)
	{
		prompt = L"Password>";
	}

	UniPrint(L"%s", prompt);
	ConsoleWriteOutFile(c, prompt, false);

	if (PasswordPrompt(tmp, sizeof(tmp)))
	{
		ConsoleWriteOutFile(c, L"********", true);
		return CopyStr(tmp);
	}
	else
	{
		ConsoleWriteOutFile(c, _UU("CON_USER_CANCEL"), true);
		return NULL;
	}
}