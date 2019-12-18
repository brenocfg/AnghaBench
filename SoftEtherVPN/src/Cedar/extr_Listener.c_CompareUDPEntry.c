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
struct TYPE_2__ {scalar_t__ SessionKey32; } ;
typedef  TYPE_1__ UDP_ENTRY ;

/* Variables and functions */

int CompareUDPEntry(void *p1, void *p2)
{
	UDP_ENTRY *e1, *e2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	e1 = *(UDP_ENTRY **)p1;
	e2 = *(UDP_ENTRY **)p2;
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	if (e1->SessionKey32 > e2->SessionKey32)
	{
		return 1;
	}
	else if (e1->SessionKey32 == e2->SessionKey32)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}