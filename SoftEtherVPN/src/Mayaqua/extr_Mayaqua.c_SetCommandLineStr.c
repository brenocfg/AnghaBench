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

/* Variables and functions */
 int /*<<< orphan*/ * CopyStr (char*) ; 
 int /*<<< orphan*/ * CopyStrToUni (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseCommandLineTokens () ; 
 int /*<<< orphan*/ * cmdline ; 
 int /*<<< orphan*/ * uni_cmdline ; 

void SetCommandLineStr(char *str)
{
	// Validate arguments
	if (str == NULL)
	{
		if (cmdline != NULL)
		{
			Free(cmdline);
		}
		cmdline = NULL;
	}
	else
	{
		if (cmdline != NULL)
		{
			Free(cmdline);
		}
		cmdline = CopyStr(str);
	}

	if (cmdline == NULL)
	{
		if (uni_cmdline != NULL)
		{
			Free(uni_cmdline);
			uni_cmdline = NULL;
		}
	}
	else
	{
		if (uni_cmdline != NULL)
		{
			Free(uni_cmdline);
		}
		uni_cmdline = CopyStrToUni(cmdline);
	}

	ParseCommandLineTokens();
}