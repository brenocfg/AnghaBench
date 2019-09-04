#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_7__ {scalar_t__ Param; } ;
struct TYPE_6__ {int /*<<< orphan*/ * InBuf; } ;
typedef  TYPE_1__ LOCAL_CONSOLE_PARAM ;
typedef  TYPE_2__ CONSOLE ;

/* Variables and functions */
 char* ConsoleReadNextFromInFile (TYPE_2__*) ; 
 int /*<<< orphan*/  ConsoleWriteOutFile (TYPE_2__*,char*,int) ; 
 char* Prompt (char*) ; 
 int /*<<< orphan*/  UniPrint (char*,char*) ; 
 char* _UU (char*) ; 

wchar_t *ConsoleLocalReadLine(CONSOLE *c, wchar_t *prompt, bool nofile)
{
	wchar_t *ret;
	LOCAL_CONSOLE_PARAM *p;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}
	p = (LOCAL_CONSOLE_PARAM *)c->Param;
	if (prompt == NULL)
	{
		prompt = L">";
	}

	ConsoleWriteOutFile(c, prompt, false);

	if (nofile == false && p->InBuf != NULL)
	{
		// Read the next line from the file
		ret = ConsoleReadNextFromInFile(c);

		if (ret != NULL)
		{
			// Display the pseudo prompt
			UniPrint(L"%s", prompt);

			// Display on the screen
			UniPrint(L"%s\n", ret);
		}
	}
	else
	{
		// Read the following line from the console
		ret = Prompt(prompt);
	}

	if (ret != NULL)
	{
		ConsoleWriteOutFile(c, ret, true);
	}
	else
	{
		ConsoleWriteOutFile(c, _UU("CON_USER_CANCEL"), true);
	}

	return ret;
}