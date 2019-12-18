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
typedef  scalar_t__ UINT ;

/* Variables and functions */

UINT Power(UINT a, UINT b)
{
	UINT ret, i;
	if (a == 0)
	{
		return 0;
	}
	if (b == 0)
	{
		return 1;
	}

	ret = 1;
	for (i = 0;i < b;i++)
	{
		ret *= a;
	}

	return ret;
}