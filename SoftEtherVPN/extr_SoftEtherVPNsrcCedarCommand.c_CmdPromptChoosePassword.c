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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 char* CmdPasswordPrompt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 

wchar_t *CmdPromptChoosePassword(CONSOLE *c, void *param)
{
	char *s;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}

	s = CmdPasswordPrompt(c);

	if (s == NULL)
	{
		return NULL;
	}
	else
	{
		wchar_t *ret = CopyStrToUni(s);

		Free(s);

		return ret;
	}
}