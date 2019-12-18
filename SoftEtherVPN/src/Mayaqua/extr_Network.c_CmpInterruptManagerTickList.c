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
typedef  scalar_t__ UINT64 ;

/* Variables and functions */

int CmpInterruptManagerTickList(void *p1, void *p2)
{
	UINT64 *v1, *v2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}

	v1 = *(UINT64 **)p1;
	v2 = *(UINT64 **)p2;
	if (v1 == NULL || v2 == NULL)
	{
		return 0;
	}

	if (*v1 > *v2)
	{
		return 1;
	}
	else if (*v1 < *v2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}