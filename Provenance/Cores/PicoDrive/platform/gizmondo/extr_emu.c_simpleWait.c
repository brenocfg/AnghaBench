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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  spend_cycles (int) ; 

__attribute__((used)) static void simpleWait(DWORD until)
{
	DWORD tval;
	int diff;

	tval = GetTickCount();
	diff = (int)until - (int)tval;
	if (diff >= 2)
		Sleep(diff - 1);

	while ((tval = GetTickCount()) < until && until - tval < 512) // some simple overflow detection
		spend_cycles(1024*2);
}