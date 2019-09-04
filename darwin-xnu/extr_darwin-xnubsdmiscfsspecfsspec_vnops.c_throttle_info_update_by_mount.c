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
typedef  TYPE_1__* uthread_t ;
typedef  void _throttle_io_info_t ;
typedef  TYPE_2__* mount_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {size_t mnt_devbsdunit; } ;
struct TYPE_7__ {int /*<<< orphan*/  uu_lowpri_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LOWPRI_MAX_NUM_DEV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _throttle_io_info ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ disk_conditioner_mount_is_ssd (TYPE_2__*) ; 
 TYPE_1__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throttle_info_set_initial_window (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *throttle_info_update_by_mount(mount_t mp)
{
	struct _throttle_io_info_t *info;
	uthread_t ut;
	boolean_t isssd = FALSE;

	ut = get_bsdthread_info(current_thread());

	if (mp != NULL) {
		if (disk_conditioner_mount_is_ssd(mp))
			isssd = TRUE;
		info = &_throttle_io_info[mp->mnt_devbsdunit];
	} else
		info = &_throttle_io_info[LOWPRI_MAX_NUM_DEV - 1];

	if (!ut->uu_lowpri_window)
		throttle_info_set_initial_window(ut, info, FALSE, isssd);

	return info;
}