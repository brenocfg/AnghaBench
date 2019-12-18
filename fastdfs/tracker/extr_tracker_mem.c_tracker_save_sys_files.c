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
 int tracker_save_groups () ; 
 int tracker_save_storages () ; 
 int tracker_save_sync_timestamps () ; 

int tracker_save_sys_files()
{
	int result;

	if ((result=tracker_save_groups()) != 0)
	{
		return result;
	}

	if ((result=tracker_save_storages()) != 0)
	{
		return result;
	}

	return tracker_save_sync_timestamps();
}