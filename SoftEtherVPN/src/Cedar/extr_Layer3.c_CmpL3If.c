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
struct TYPE_2__ {int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ L3IF ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CmpL3If(void *p1, void *p2)
{
	L3IF *f1, *f2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	f1 = *(L3IF **)p1;
	f2 = *(L3IF **)p2;
	if (f1 == NULL || f2 == NULL)
	{
		return 0;
	}

	return StrCmpi(f1->HubName, f2->HubName);
}