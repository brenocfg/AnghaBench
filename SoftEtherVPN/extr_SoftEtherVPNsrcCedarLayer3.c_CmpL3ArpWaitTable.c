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
struct TYPE_2__ {scalar_t__ IpAddress; } ;
typedef  TYPE_1__ L3ARPWAIT ;

/* Variables and functions */

int CmpL3ArpWaitTable(void *p1, void *p2)
{
	L3ARPWAIT *w1, *w2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	w1 = *(L3ARPWAIT **)p1;
	w2 = *(L3ARPWAIT **)p2;
	if (w1 == NULL || w2 == NULL)
	{
		return 0;
	}
	if (w1->IpAddress > w2->IpAddress)
	{
		return 1;
	}
	else if (w1->IpAddress < w2->IpAddress)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}