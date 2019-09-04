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
 int /*<<< orphan*/  ConsoleWriteOutFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ UniEndWith (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UniPrint (char*,int /*<<< orphan*/ *,char*) ; 

bool ConsoleLocalWrite(CONSOLE *c, wchar_t *str)
{
	// Validate arguments
	if (c == NULL || str == NULL)
	{
		return false;
	}

	UniPrint(L"%s%s", str, (UniEndWith(str, L"\n") ? L"" : L"\n"));

	ConsoleWriteOutFile(c, str, true);

	return true;
}