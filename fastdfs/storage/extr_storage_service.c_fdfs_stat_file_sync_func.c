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
 scalar_t__ g_stat_change_count ; 
 scalar_t__ last_stat_change_count ; 
 int storage_write_to_stat_file () ; 

int fdfs_stat_file_sync_func(void *args)
{
	int result;

	if (last_stat_change_count !=  g_stat_change_count)
	{
		if ((result=storage_write_to_stat_file()) == 0)
		{
			last_stat_change_count = g_stat_change_count;
		}

		return result;
	}
	else
	{
		return 0;
	}
}