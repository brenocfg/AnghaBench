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
struct TYPE_2__ {scalar_t__ UpdateTime; } ;
typedef  TYPE_1__ ERASE_FILE ;

/* Variables and functions */

int CompareEraseFile(void *p1, void *p2)
{
	ERASE_FILE *f1, *f2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	f1 = *(ERASE_FILE **)p1;
	f2 = *(ERASE_FILE **)p2;
	if (f1 == NULL || f2 == NULL)
	{
		return 0;
	}
	if (f1->UpdateTime > f2->UpdateTime)
	{
		return 1;
	}
	else if (f1->UpdateTime == f2->UpdateTime)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}