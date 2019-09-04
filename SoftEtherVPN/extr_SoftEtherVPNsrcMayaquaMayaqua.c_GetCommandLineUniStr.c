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
 int /*<<< orphan*/ * UniCopyStr (char*) ; 
 char* uni_cmdline ; 

wchar_t *GetCommandLineUniStr()
{
	if (uni_cmdline == NULL)
	{
		return UniCopyStr(L"");
	}
	else
	{
		return UniCopyStr(uni_cmdline);
	}
}