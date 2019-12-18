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

/* Variables and functions */
 int /*<<< orphan*/ * CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseCommandLineTokens () ; 
 int /*<<< orphan*/ * uni_cmdline ; 

void SetCommandLineUniStr(wchar_t *str)
{
	if (uni_cmdline != NULL)
	{
		Free(uni_cmdline);
	}
	if (str == NULL)
	{
		uni_cmdline = NULL;
	}
	else
	{
		uni_cmdline = CopyUniStr(str);
	}

	ParseCommandLineTokens();
}