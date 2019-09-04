#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {scalar_t__ ConsoleType; int /*<<< orphan*/  OutputLock; } ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 scalar_t__ CONSOLE_LOCAL ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int UniEndWith (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UniPrint (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCat (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void PtTrafficPrintProc(void *param, wchar_t *str)
{
	CONSOLE *c;
	// Validate arguments
	if (param == NULL || str == NULL)
	{
		return;
	}

	c = (CONSOLE *)param;

	if (c->ConsoleType == CONSOLE_LOCAL)
	{
		Lock(c->OutputLock);
		{
			wchar_t tmp[MAX_SIZE];

			// Display only if the local console
			// (Can not be displayed because threads aren't synchronized otherwise?)
			UniStrCpy(tmp, sizeof(tmp), str);
			if (UniEndWith(str, L"\n") == false)
			{
				UniStrCat(tmp, sizeof(tmp), L"\n");
			}
			UniPrint(L"%s", tmp);
		}
		Unlock(c->OutputLock);
	}
}