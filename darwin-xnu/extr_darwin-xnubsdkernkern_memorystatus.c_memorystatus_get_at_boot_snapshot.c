#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notification_time; } ;
typedef  TYPE_1__ memorystatus_jetsam_snapshot_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 TYPE_1__ memorystatus_at_boot_snapshot ; 

__attribute__((used)) static int
memorystatus_get_at_boot_snapshot(memorystatus_jetsam_snapshot_t **snapshot, size_t *snapshot_size, boolean_t size_only) {
	size_t input_size = *snapshot_size;

	/*
	 * The at_boot snapshot has no entry list.
	 */
	*snapshot_size = sizeof(memorystatus_jetsam_snapshot_t);

	if (size_only) {
		return 0;
	}

	/*
	 * Validate the size of the snapshot buffer
	 */
	if (input_size < *snapshot_size) {
		return EINVAL;
	}

	/*
	 * Update the notification_time only
	 */
	memorystatus_at_boot_snapshot.notification_time = mach_absolute_time();
	*snapshot = &memorystatus_at_boot_snapshot;

	MEMORYSTATUS_DEBUG(7, "memorystatus_get_at_boot_snapshot: returned inputsize (%ld), snapshot_size(%ld), listcount(%d)\n",
			   (long)input_size, (long)*snapshot_size, 0);
	return 0;
}