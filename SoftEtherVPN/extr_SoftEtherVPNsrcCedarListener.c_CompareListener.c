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
struct TYPE_2__ {scalar_t__ Protocol; scalar_t__ Port; } ;
typedef  TYPE_1__ LISTENER ;

/* Variables and functions */

int CompareListener(void *p1, void *p2)
{
	LISTENER *r1, *r2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	r1 = *(LISTENER **)p1;
	r2 = *(LISTENER **)p2;
	if (r1 == NULL || r2 == NULL)
	{
		return 0;
	}

	if (r1->Protocol > r2->Protocol)
	{
		return 1;
	}
	else if (r1->Protocol < r2->Protocol)
	{
		return -1;
	}
	else if (r1->Port > r2->Port)
	{
		return 1;
	}
	else if (r1->Port < r2->Port)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}