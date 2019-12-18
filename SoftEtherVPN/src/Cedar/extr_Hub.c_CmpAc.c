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
struct TYPE_2__ {scalar_t__ Priority; scalar_t__ Deny; } ;
typedef  TYPE_1__ AC ;

/* Variables and functions */

int CmpAc(void *p1, void *p2)
{
	AC *a1, *a2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	a1 = *(AC **)p1;
	a2 = *(AC **)p2;
	if (a1 == NULL || a2 == NULL)
	{
		return 0;
	}
	if (a1->Priority > a2->Priority)
	{
		return 1;
	}
	else if (a1->Priority < a2->Priority)
	{
		return -1;
	}
	else if (a1->Deny > a2->Deny)
	{
		return 1;
	}
	else if (a1->Deny < a2->Deny)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}