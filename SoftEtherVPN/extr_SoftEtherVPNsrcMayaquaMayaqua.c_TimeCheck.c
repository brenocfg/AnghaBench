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

/* Variables and functions */

void TimeCheck()
{
#ifdef OS_WIN32
	UINT now, ret, total;
	now = Win32GetTick();
	if (last_time_check == 0)
	{
		ret = 0;
	}
	else
	{
		ret = now - last_time_check;
	}
	last_time_check = now;

	if (first_time_check == 0)
	{
		first_time_check = now;
	}

	total = now - first_time_check;

	printf(" -- %3.3f / %3.3f\n", (double)ret / 1000.0f, (double)total / 1000.0f);
#endif	// OS_WIN32
}