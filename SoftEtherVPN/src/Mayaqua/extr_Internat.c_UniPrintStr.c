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
 char* CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  Win32PrintW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void UniPrintStr(wchar_t *string)
{
	// Validate arguments
	if (string == NULL)
	{
		return;
	}

#ifdef	OS_UNIX
	if (true)
	{
		char *str = CopyUniToStr(string);

		if (str != NULL)
		{
			fputs(str, stdout);
		}
		else
		{
			fputs("", stdout);
		}

		Free(str);
	}
#else	// OS_UNIX
	Win32PrintW(string);
#endif	// OS_UNIX
}