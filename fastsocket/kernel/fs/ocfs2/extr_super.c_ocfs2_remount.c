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
struct super_block {int s_flags; } ;
struct ocfs2_super {int s_mount_opt; int osb_flags; int s_feature_incompat; scalar_t__ osb_commit_interval; int /*<<< orphan*/  preferred_slot; int /*<<< orphan*/  s_atime_quantum; int /*<<< orphan*/  osb_lock; } ;
struct mount_options {int mount_opt; scalar_t__ commit_interval; int /*<<< orphan*/  slot; int /*<<< orphan*/  atime_quantum; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int MS_RDONLY ; 
 int OCFS2_FEATURE_INCOMPAT_XATTR ; 
 int /*<<< orphan*/  OCFS2_FEATURE_RO_COMPAT_SUPP ; 
 int OCFS2_HAS_RO_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int OCFS2_MOUNT_DATA_WRITEBACK ; 
 int OCFS2_MOUNT_HB_LOCAL ; 
 int OCFS2_MOUNT_INODE64 ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 int OCFS2_OSB_ERROR_FS ; 
 int OCFS2_OSB_HARD_RO ; 
 int OCFS2_OSB_SOFT_RO ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int ocfs2_enable_quotas (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_parse_options (struct super_block*,char*,struct mount_options*,int) ; 
 int /*<<< orphan*/  ocfs2_set_journal_params (struct ocfs2_super*) ; 
 int ocfs2_susp_quotas (struct ocfs2_super*,int) ; 
 scalar_t__ sb_any_quota_suspended (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ocfs2_remount(struct super_block *sb, int *flags, char *data)
{
	int incompat_features;
	int ret = 0;
	struct mount_options parsed_options;
	struct ocfs2_super *osb = OCFS2_SB(sb);

	lock_kernel();

	if (!ocfs2_parse_options(sb, data, &parsed_options, 1)) {
		ret = -EINVAL;
		goto out;
	}

	if ((osb->s_mount_opt & OCFS2_MOUNT_HB_LOCAL) !=
	    (parsed_options.mount_opt & OCFS2_MOUNT_HB_LOCAL)) {
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot change heartbeat mode on remount\n");
		goto out;
	}

	if ((osb->s_mount_opt & OCFS2_MOUNT_DATA_WRITEBACK) !=
	    (parsed_options.mount_opt & OCFS2_MOUNT_DATA_WRITEBACK)) {
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot change data mode on remount\n");
		goto out;
	}

	/* Probably don't want this on remount; it might
	 * mess with other nodes */
	if (!(osb->s_mount_opt & OCFS2_MOUNT_INODE64) &&
	    (parsed_options.mount_opt & OCFS2_MOUNT_INODE64)) {
		ret = -EINVAL;
		mlog(ML_ERROR, "Cannot enable inode64 on remount\n");
		goto out;
	}

	/* We're going to/from readonly mode. */
	if ((*flags & MS_RDONLY) != (sb->s_flags & MS_RDONLY)) {
		/* Disable quota accounting before remounting RO */
		if (*flags & MS_RDONLY) {
			ret = ocfs2_susp_quotas(osb, 0);
			if (ret < 0)
				goto out;
		}
		/* Lock here so the check of HARD_RO and the potential
		 * setting of SOFT_RO is atomic. */
		spin_lock(&osb->osb_lock);
		if (osb->osb_flags & OCFS2_OSB_HARD_RO) {
			mlog(ML_ERROR, "Remount on readonly device is forbidden.\n");
			ret = -EROFS;
			goto unlock_osb;
		}

		if (*flags & MS_RDONLY) {
			mlog(0, "Going to ro mode.\n");
			sb->s_flags |= MS_RDONLY;
			osb->osb_flags |= OCFS2_OSB_SOFT_RO;
		} else {
			mlog(0, "Making ro filesystem writeable.\n");

			if (osb->osb_flags & OCFS2_OSB_ERROR_FS) {
				mlog(ML_ERROR, "Cannot remount RDWR "
				     "filesystem due to previous errors.\n");
				ret = -EROFS;
				goto unlock_osb;
			}
			incompat_features = OCFS2_HAS_RO_COMPAT_FEATURE(sb, ~OCFS2_FEATURE_RO_COMPAT_SUPP);
			if (incompat_features) {
				mlog(ML_ERROR, "Cannot remount RDWR because "
				     "of unsupported optional features "
				     "(%x).\n", incompat_features);
				ret = -EINVAL;
				goto unlock_osb;
			}
			sb->s_flags &= ~MS_RDONLY;
			osb->osb_flags &= ~OCFS2_OSB_SOFT_RO;
		}
unlock_osb:
		spin_unlock(&osb->osb_lock);
		/* Enable quota accounting after remounting RW */
		if (!ret && !(*flags & MS_RDONLY)) {
			if (sb_any_quota_suspended(sb))
				ret = ocfs2_susp_quotas(osb, 1);
			else
				ret = ocfs2_enable_quotas(osb);
			if (ret < 0) {
				/* Return back changes... */
				spin_lock(&osb->osb_lock);
				sb->s_flags |= MS_RDONLY;
				osb->osb_flags |= OCFS2_OSB_SOFT_RO;
				spin_unlock(&osb->osb_lock);
				goto out;
			}
		}
	}

	if (!ret) {
		/* Only save off the new mount options in case of a successful
		 * remount. */
		if (!(osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_XATTR))
			parsed_options.mount_opt &= ~OCFS2_MOUNT_POSIX_ACL;
		osb->s_mount_opt = parsed_options.mount_opt;
		osb->s_atime_quantum = parsed_options.atime_quantum;
		osb->preferred_slot = parsed_options.slot;
		if (parsed_options.commit_interval)
			osb->osb_commit_interval = parsed_options.commit_interval;

		if (!ocfs2_is_hard_readonly(osb))
			ocfs2_set_journal_params(osb);
	}
out:
	unlock_kernel();
	return ret;
}