#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
struct TYPE_8__ {void* entry_count; } ;
typedef  TYPE_1__ memorystatus_jetsam_snapshot_t ;
typedef  int int32_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FALSE ; 
 int MEMORYSTATUS_SNAPSHOT_AT_BOOT ; 
 int MEMORYSTATUS_SNAPSHOT_COPY ; 
 int MEMORYSTATUS_SNAPSHOT_ON_DEMAND ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int copyout (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memorystatus_get_at_boot_snapshot (TYPE_1__**,size_t*,scalar_t__) ; 
 int memorystatus_get_jetsam_snapshot (TYPE_1__**,size_t*,scalar_t__) ; 
 int memorystatus_get_jetsam_snapshot_copy (TYPE_1__**,size_t*,scalar_t__) ; 
 int memorystatus_get_on_demand_snapshot (TYPE_1__**,size_t*,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_jetsam_snapshot ; 
 int /*<<< orphan*/  memorystatus_jetsam_snapshot_copy ; 
 void* memorystatus_jetsam_snapshot_copy_count ; 
 void* memorystatus_jetsam_snapshot_count ; 
 scalar_t__ memorystatus_jetsam_snapshot_last_timestamp ; 
 int /*<<< orphan*/  memorystatus_jetsam_snapshot_size ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

__attribute__((used)) static int
memorystatus_cmd_get_jetsam_snapshot(int32_t flags, user_addr_t buffer, size_t buffer_size, int32_t *retval) {
	int error = EINVAL;
	boolean_t size_only;
	boolean_t is_default_snapshot = FALSE;
	boolean_t is_on_demand_snapshot = FALSE;
	boolean_t is_at_boot_snapshot = FALSE;
	memorystatus_jetsam_snapshot_t *snapshot;

	size_only = ((buffer == USER_ADDR_NULL) ? TRUE : FALSE);

	if (flags == 0) {
		/* Default */
		is_default_snapshot = TRUE;
		error = memorystatus_get_jetsam_snapshot(&snapshot, &buffer_size, size_only);
	} else {
		if (flags & ~(MEMORYSTATUS_SNAPSHOT_ON_DEMAND | MEMORYSTATUS_SNAPSHOT_AT_BOOT | MEMORYSTATUS_SNAPSHOT_COPY)) {
			/*
			 * Unsupported bit set in flag.
			 */
			return EINVAL;
		}

		if (flags & (flags - 0x1)) {
			/*
			 * Can't have multiple flags set at the same time.
			 */
			return EINVAL;
		}

		if (flags & MEMORYSTATUS_SNAPSHOT_ON_DEMAND) {
			is_on_demand_snapshot = TRUE;
			/*
			 * When not requesting the size only, the following call will allocate
			 * an on_demand snapshot buffer, which is freed below.
			 */
			error = memorystatus_get_on_demand_snapshot(&snapshot, &buffer_size, size_only);

		} else if (flags & MEMORYSTATUS_SNAPSHOT_AT_BOOT) {
			is_at_boot_snapshot = TRUE;
			error = memorystatus_get_at_boot_snapshot(&snapshot, &buffer_size, size_only);
		} else if (flags & MEMORYSTATUS_SNAPSHOT_COPY) {
			error = memorystatus_get_jetsam_snapshot_copy(&snapshot, &buffer_size, size_only);
		} else {
			/*
			 * Invalid flag setting.
			 */
			return EINVAL;
		}
	}

	if (error) {
		goto out;
	}

	/*
	 * Copy the data out to user space and clear the snapshot buffer.
	 * If working with the jetsam snapshot,
	 *	clearing the buffer means, reset the count.
	 * If working with an on_demand snapshot
	 *	clearing the buffer means, free it.
	 * If working with the at_boot snapshot
	 *	there is nothing to clear or update.
	 * If working with a copy of the snapshot
	 *	there is nothing to clear or update.
	 */
	if (!size_only) {
		if ((error = copyout(snapshot, buffer, buffer_size)) == 0) {
			if (is_default_snapshot) {
				/*
				 * The jetsam snapshot is never freed, its count is simply reset.
				 * However, we make a copy for any parties that might be interested
				 * in the previous fully populated snapshot.
				 */
				proc_list_lock();
				memcpy(memorystatus_jetsam_snapshot_copy, memorystatus_jetsam_snapshot, memorystatus_jetsam_snapshot_size);
				memorystatus_jetsam_snapshot_copy_count = memorystatus_jetsam_snapshot_count;
				snapshot->entry_count = memorystatus_jetsam_snapshot_count = 0;
				memorystatus_jetsam_snapshot_last_timestamp = 0;
				proc_list_unlock();
			}
		}

		if (is_on_demand_snapshot) {
			/*
			 * The on_demand snapshot is always freed,
			 * even if the copyout failed.
			 */
			if(snapshot) {
				kfree(snapshot, buffer_size);
			}
		}
	}

	if (error == 0) {
		*retval = buffer_size;
	}
out:
	return error;
}