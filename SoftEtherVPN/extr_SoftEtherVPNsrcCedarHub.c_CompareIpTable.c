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
struct TYPE_2__ {int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ IP_TABLE_ENTRY ;

/* Variables and functions */
 int CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CompareIpTable(void *p1, void *p2)
{
	IP_TABLE_ENTRY *e1, *e2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	e1 = *(IP_TABLE_ENTRY **)p1;
	e2 = *(IP_TABLE_ENTRY **)p2;
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}
	return CmpIpAddr(&e1->Ip, &e2->Ip);
}