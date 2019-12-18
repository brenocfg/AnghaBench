#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lockgroup_info_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_8__ {scalar_t__ lock_rw_wait_cnt; scalar_t__ lock_rw_miss_cnt; scalar_t__ lock_rw_util_cnt; scalar_t__ lock_mtx_held_cnt; scalar_t__ lock_mtx_wait_cnt; scalar_t__ lock_mtx_miss_cnt; scalar_t__ lock_mtx_util_cnt; scalar_t__ lock_spin_miss_cnt; scalar_t__ lock_spin_util_cnt; } ;
struct TYPE_7__ {scalar_t__ lock_rw_wait_cnt; scalar_t__ lock_rw_miss_cnt; scalar_t__ lock_rw_util_cnt; scalar_t__ lock_mtx_held_cnt; scalar_t__ lock_mtx_wait_cnt; scalar_t__ lock_mtx_miss_cnt; scalar_t__ lock_mtx_util_cnt; scalar_t__ lock_spin_miss_cnt; scalar_t__ lock_spin_util_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int count ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_control ; 
 scalar_t__ host_lockgroup_info (int /*<<< orphan*/ ,TYPE_2__**,int*) ; 
 TYPE_1__* lockgroup_deltas ; 
 TYPE_2__* lockgroup_info ; 
 TYPE_1__* lockgroup_start ; 
 int /*<<< orphan*/  mach_error (char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 

void
get_lockgroup_deltas(void)
{
	kern_return_t 			kr;
	unsigned int			i;

	kr = host_lockgroup_info(host_control, &lockgroup_info, &count);

	if (kr != KERN_SUCCESS)
	{
		mach_error("host_statistics", kr);
		exit (EXIT_FAILURE);
	}

	memcpy(lockgroup_deltas, lockgroup_info, count * sizeof(lockgroup_info_t));
	for (i = 0; i < count; i++) {
		lockgroup_deltas[i].lock_spin_util_cnt =
		    lockgroup_info[i].lock_spin_util_cnt -
		    lockgroup_start[i].lock_spin_util_cnt;
		lockgroup_deltas[i].lock_spin_miss_cnt =
		    lockgroup_info[i].lock_spin_miss_cnt -
		    lockgroup_start[i].lock_spin_miss_cnt;
		lockgroup_deltas[i].lock_mtx_util_cnt =
		    lockgroup_info[i].lock_mtx_util_cnt -
		    lockgroup_start[i].lock_mtx_util_cnt;
		lockgroup_deltas[i].lock_mtx_miss_cnt =
		    lockgroup_info[i].lock_mtx_miss_cnt -
		    lockgroup_start[i].lock_mtx_miss_cnt;
		lockgroup_deltas[i].lock_mtx_wait_cnt =
		    lockgroup_info[i].lock_mtx_wait_cnt -
		    lockgroup_start[i].lock_mtx_wait_cnt;
		lockgroup_deltas[i].lock_mtx_held_cnt =
		    lockgroup_info[i].lock_mtx_held_cnt -
		    lockgroup_start[i].lock_mtx_held_cnt;
		lockgroup_deltas[i].lock_rw_util_cnt =
		    lockgroup_info[i].lock_rw_util_cnt -
		    lockgroup_start[i].lock_rw_util_cnt;
		lockgroup_deltas[i].lock_rw_miss_cnt =
		    lockgroup_info[i].lock_rw_miss_cnt -
		    lockgroup_start[i].lock_rw_miss_cnt;
		lockgroup_deltas[i].lock_rw_wait_cnt =
		    lockgroup_info[i].lock_rw_wait_cnt -
		    lockgroup_start[i].lock_rw_wait_cnt;
	}
	memcpy(lockgroup_start, lockgroup_info, count * sizeof(lockgroup_info_t));
}