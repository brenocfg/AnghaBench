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
struct TYPE_2__ {scalar_t__ VlanId; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ MAC_TABLE_ENTRY ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int CompareMacTable(void *p1, void *p2)
{
	int r;
	MAC_TABLE_ENTRY *e1, *e2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	e1 = *(MAC_TABLE_ENTRY **)p1;
	e2 = *(MAC_TABLE_ENTRY **)p2;
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}
	r = memcmp(e1->MacAddress, e2->MacAddress, 6);
	if (r != 0)
	{
		return r;
	}
	if (e1->VlanId > e2->VlanId)
	{
		return 1;
	}
	else if (e1->VlanId < e2->VlanId)
	{
		return -1;
	}
	return 0;
}