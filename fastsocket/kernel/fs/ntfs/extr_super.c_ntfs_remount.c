#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_flags; } ;
struct TYPE_10__ {int vol_flags; int major_ver; int /*<<< orphan*/  logfile_ino; } ;
typedef  TYPE_1__ ntfs_volume ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int MS_RDONLY ; 
 TYPE_1__* NTFS_SB (struct super_block*) ; 
 scalar_t__ NVolErrors (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolSetErrors (TYPE_1__*) ; 
 int VOLUME_IS_DIRTY ; 
 int VOLUME_MODIFIED_BY_CHKDSK ; 
 int VOLUME_MOUNTED_ON_NT4 ; 
 int VOLUME_MUST_MOUNT_RO_MASK ; 
 scalar_t__ le16_to_cpu (int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ ntfs_clear_volume_flags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int /*<<< orphan*/  ntfs_empty_logfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  ntfs_mark_quotas_out_of_date (TYPE_1__*) ; 
 scalar_t__ ntfs_set_volume_flags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ntfs_stamp_usnjrnl (TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_warning (struct super_block*,char*) ; 
 int /*<<< orphan*/  parse_options (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ntfs_remount(struct super_block *sb, int *flags, char *opt)
{
	ntfs_volume *vol = NTFS_SB(sb);

	ntfs_debug("Entering with remount options string: %s", opt);

	lock_kernel();
#ifndef NTFS_RW
	/* For read-only compiled driver, enforce read-only flag. */
	*flags |= MS_RDONLY;
#else /* NTFS_RW */
	/*
	 * For the read-write compiled driver, if we are remounting read-write,
	 * make sure there are no volume errors and that no unsupported volume
	 * flags are set.  Also, empty the logfile journal as it would become
	 * stale as soon as something is written to the volume and mark the
	 * volume dirty so that chkdsk is run if the volume is not umounted
	 * cleanly.  Finally, mark the quotas out of date so Windows rescans
	 * the volume on boot and updates them.
	 *
	 * When remounting read-only, mark the volume clean if no volume errors
	 * have occured.
	 */
	if ((sb->s_flags & MS_RDONLY) && !(*flags & MS_RDONLY)) {
		static const char *es = ".  Cannot remount read-write.";

		/* Remounting read-write. */
		if (NVolErrors(vol)) {
			ntfs_error(sb, "Volume has errors and is read-only%s",
					es);
			unlock_kernel();
			return -EROFS;
		}
		if (vol->vol_flags & VOLUME_IS_DIRTY) {
			ntfs_error(sb, "Volume is dirty and read-only%s", es);
			unlock_kernel();
			return -EROFS;
		}
		if (vol->vol_flags & VOLUME_MODIFIED_BY_CHKDSK) {
			ntfs_error(sb, "Volume has been modified by chkdsk "
					"and is read-only%s", es);
			unlock_kernel();
			return -EROFS;
		}
		if (vol->vol_flags & VOLUME_MUST_MOUNT_RO_MASK) {
			ntfs_error(sb, "Volume has unsupported flags set "
					"(0x%x) and is read-only%s",
					(unsigned)le16_to_cpu(vol->vol_flags),
					es);
			unlock_kernel();
			return -EROFS;
		}
		if (ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY)) {
			ntfs_error(sb, "Failed to set dirty bit in volume "
					"information flags%s", es);
			unlock_kernel();
			return -EROFS;
		}
#if 0
		// TODO: Enable this code once we start modifying anything that
		//	 is different between NTFS 1.2 and 3.x...
		/* Set NT4 compatibility flag on newer NTFS version volumes. */
		if ((vol->major_ver > 1)) {
			if (ntfs_set_volume_flags(vol, VOLUME_MOUNTED_ON_NT4)) {
				ntfs_error(sb, "Failed to set NT4 "
						"compatibility flag%s", es);
				NVolSetErrors(vol);
				return -EROFS;
			}
		}
#endif
		if (!ntfs_empty_logfile(vol->logfile_ino)) {
			ntfs_error(sb, "Failed to empty journal $LogFile%s",
					es);
			NVolSetErrors(vol);
			unlock_kernel();
			return -EROFS;
		}
		if (!ntfs_mark_quotas_out_of_date(vol)) {
			ntfs_error(sb, "Failed to mark quotas out of date%s",
					es);
			NVolSetErrors(vol);
			unlock_kernel();
			return -EROFS;
		}
		if (!ntfs_stamp_usnjrnl(vol)) {
			ntfs_error(sb, "Failed to stamp transation log "
					"($UsnJrnl)%s", es);
			NVolSetErrors(vol);
			unlock_kernel();
			return -EROFS;
		}
	} else if (!(sb->s_flags & MS_RDONLY) && (*flags & MS_RDONLY)) {
		/* Remounting read-only. */
		if (!NVolErrors(vol)) {
			if (ntfs_clear_volume_flags(vol, VOLUME_IS_DIRTY))
				ntfs_warning(sb, "Failed to clear dirty bit "
						"in volume information "
						"flags.  Run chkdsk.");
		}
	}
#endif /* NTFS_RW */

	// TODO: Deal with *flags.

	if (!parse_options(vol, opt)) {
		unlock_kernel();
		return -EINVAL;
	}
	unlock_kernel();
	ntfs_debug("Done.");
	return 0;
}