#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _throttle_io_info_t {int /*<<< orphan*/  throttle_last_write_timestamp; } ;
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {size_t mnt_devbsdunit; int /*<<< orphan*/  mnt_last_write_completed_timestamp; struct _throttle_io_info_t* mnt_throttle_info; } ;

/* Variables and functions */
 int LOWPRI_MAX_NUM_DEV ; 
 struct _throttle_io_info_t* _throttle_io_info ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 

void
update_last_io_time(mount_t mp)
{
    	struct _throttle_io_info_t *info;
		
	if (mp == NULL)
		info = &_throttle_io_info[LOWPRI_MAX_NUM_DEV - 1];
	else if (mp->mnt_throttle_info == NULL)
		info = &_throttle_io_info[mp->mnt_devbsdunit];
	else
		info = mp->mnt_throttle_info;

	microuptime(&info->throttle_last_write_timestamp);
	if (mp != NULL)
		mp->mnt_last_write_completed_timestamp = info->throttle_last_write_timestamp;
}