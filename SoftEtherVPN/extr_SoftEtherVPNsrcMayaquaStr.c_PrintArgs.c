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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 char* CopyStrToUni (char*) ; 
 char* CopyUniToStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* InternalFormatArgs (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PrintStr (char*) ; 

void PrintArgs(char *fmt, va_list args)
{
	wchar_t *ret;
	wchar_t *fmt_wchar;
	char *tmp;
	// Validate arguments
	if (fmt == NULL)
	{
		return;
	}

	fmt_wchar = CopyStrToUni(fmt);
	ret = InternalFormatArgs(fmt_wchar, args, true);

	tmp = CopyUniToStr(ret);
	PrintStr(tmp);
	Free(tmp);

	Free(ret);
	Free(fmt_wchar);
}