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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_t ;
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_entry_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,long,long,long) ; 
 scalar_t__ kalloc (size_t) ; 
 int /*<<< orphan*/  memorystatus_init_jetsam_snapshot_locked (int /*<<< orphan*/ *,int) ; 
 int memorystatus_list_count ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

__attribute__((used)) static int
memorystatus_get_on_demand_snapshot(memorystatus_jetsam_snapshot_t **snapshot, size_t *snapshot_size, boolean_t size_only) {
	size_t input_size = *snapshot_size;
	uint32_t ods_list_count = memorystatus_list_count;
	memorystatus_jetsam_snapshot_t *ods = NULL;	/* The on_demand snapshot buffer */

	*snapshot_size = sizeof(memorystatus_jetsam_snapshot_t) + (sizeof(memorystatus_jetsam_snapshot_entry_t) * (ods_list_count));

	if (size_only) {
		return 0;
	}

	/*
	 * Validate the size of the snapshot buffer.
	 * This is inherently racey. May want to revisit
	 * this error condition and trim the output when
	 * it doesn't fit.
	 */
	if (input_size < *snapshot_size) {
		return EINVAL;
	}

	/*
	 * Allocate and initialize a snapshot buffer.
	 */
	ods = (memorystatus_jetsam_snapshot_t *)kalloc(*snapshot_size);
	if (!ods) {
		return (ENOMEM);
	}

	memset(ods, 0, *snapshot_size);

	proc_list_lock();
	memorystatus_init_jetsam_snapshot_locked(ods, ods_list_count);
	proc_list_unlock();

	/*
	 * Return the kernel allocated, on_demand buffer.
	 * The caller of this routine will copy the data out
	 * to user space and then free the kernel allocated
	 * buffer.
	 */
	*snapshot = ods;

	MEMORYSTATUS_DEBUG(7, "memorystatus_get_on_demand_snapshot: returned inputsize (%ld), snapshot_size(%ld), listcount(%ld)\n",
				   (long)input_size, (long)*snapshot_size, (long)ods_list_count);
	
	return 0;
}