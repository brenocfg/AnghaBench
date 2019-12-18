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
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniPrintStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void PrintStr(char *str)
{
	wchar_t *unistr = NULL;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

#ifdef	OS_UNIX
	fputs(str, stdout);
#else	// OS_UNIX
	unistr = CopyStrToUni(str);
	UniPrintStr(unistr);
	Free(unistr);
#endif	// OS_UNIX
}