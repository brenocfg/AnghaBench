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
struct mirror_set {int nr_mirrors; int /*<<< orphan*/ * mirror; } ;
struct dm_region {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*,...) ; 
 int /*<<< orphan*/  DM_RAID1_SYNC_ERROR ; 
 int /*<<< orphan*/  dm_rh_recovery_end (struct dm_region*,int) ; 
 struct mirror_set* dm_rh_region_context (struct dm_region*) ; 
 int /*<<< orphan*/  fail_mirror (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_default_mirror (struct mirror_set*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static void recovery_complete(int read_err, unsigned long write_err,
			      void *context)
{
	struct dm_region *reg = context;
	struct mirror_set *ms = dm_rh_region_context(reg);
	int m, bit = 0;

	if (read_err) {
		/* Read error means the failure of default mirror. */
		DMERR_LIMIT("Unable to read primary mirror during recovery");
		fail_mirror(get_default_mirror(ms), DM_RAID1_SYNC_ERROR);
	}

	if (write_err) {
		DMERR_LIMIT("Write error during recovery (error = 0x%lx)",
			    write_err);
		/*
		 * Bits correspond to devices (excluding default mirror).
		 * The default mirror cannot change during recovery.
		 */
		for (m = 0; m < ms->nr_mirrors; m++) {
			if (&ms->mirror[m] == get_default_mirror(ms))
				continue;
			if (test_bit(bit, &write_err))
				fail_mirror(ms->mirror + m,
					    DM_RAID1_SYNC_ERROR);
			bit++;
		}
	}

	dm_rh_recovery_end(reg, !(read_err || write_err));
}