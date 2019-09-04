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
struct TYPE_2__ {scalar_t__ Id; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;

/* Variables and functions */

int SortObjectView(void *p1, void *p2)
{
	TRACKING_OBJECT *o1, *o2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	o1 = *(TRACKING_OBJECT **)p1;
	o2 = *(TRACKING_OBJECT **)p2;
	if (o1 == NULL || o2 == NULL)
	{
		return 0;
	}

	if (o1->Id > o2->Id)
	{
		return 1;
	}
	else if (o1->Id == o2->Id)
	{
		return 0;
	}
	return -1;
}