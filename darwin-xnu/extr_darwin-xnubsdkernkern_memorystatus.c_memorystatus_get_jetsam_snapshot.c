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
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_t ;
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_entry_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,long,long,long) ; 
 int /*<<< orphan*/ * memorystatus_jetsam_snapshot ; 
 int memorystatus_jetsam_snapshot_count ; 

__attribute__((used)) static int
memorystatus_get_jetsam_snapshot(memorystatus_jetsam_snapshot_t **snapshot, size_t *snapshot_size, boolean_t size_only) {
	size_t input_size = *snapshot_size;

	if (memorystatus_jetsam_snapshot_count > 0) {
		*snapshot_size = sizeof(memorystatus_jetsam_snapshot_t) + (sizeof(memorystatus_jetsam_snapshot_entry_t) * (memorystatus_jetsam_snapshot_count));
	} else {
		*snapshot_size = 0;
	}

	if (size_only) {
		return 0;
	}

	if (input_size < *snapshot_size) {
		return EINVAL;
	}

	*snapshot = memorystatus_jetsam_snapshot;

	MEMORYSTATUS_DEBUG(7, "memorystatus_get_jetsam_snapshot: returned inputsize (%ld), snapshot_size(%ld), listcount(%ld)\n",
				   (long)input_size, (long)*snapshot_size, (long)memorystatus_jetsam_snapshot_count);

	return 0;
}