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
struct super_block {int s_flags; struct gfs2_sbd* s_fs_info; } ;
struct gfs2_tune {int gt_statfs_slow; int gt_statfs_quantum; int /*<<< orphan*/  gt_spin; int /*<<< orphan*/  gt_quota_quantum; int /*<<< orphan*/  gt_log_flush_secs; } ;
struct gfs2_args {int ar_statfs_quantum; int /*<<< orphan*/  ar_quota_quantum; int /*<<< orphan*/  ar_commit; scalar_t__ ar_nobarrier; scalar_t__ ar_posix_acl; scalar_t__ ar_spectator; int /*<<< orphan*/  ar_hostdata; int /*<<< orphan*/  ar_locktable; int /*<<< orphan*/  ar_lockproto; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; struct gfs2_args sd_args; struct gfs2_tune sd_tune; } ;

/* Variables and functions */
 int EINVAL ; 
 int MS_POSIXACL ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  SDF_NOBARRIERS ; 
 scalar_t__ args_neq (struct gfs2_args*,struct gfs2_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gfs2_make_fs_ro (struct gfs2_sbd*) ; 
 int gfs2_make_fs_rw (struct gfs2_sbd*) ; 
 int gfs2_mount_args (struct gfs2_args*,char*) ; 
 int /*<<< orphan*/  gfs2_online_uevent (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  ignore_local_fs ; 
 int /*<<< orphan*/  localcaching ; 
 int /*<<< orphan*/  localflocks ; 
 int /*<<< orphan*/  meta ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spectator ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_remount_fs(struct super_block *sb, int *flags, char *data)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct gfs2_args args = sdp->sd_args; /* Default to current settings */
	struct gfs2_tune *gt = &sdp->sd_tune;
	int error;

	spin_lock(&gt->gt_spin);
	args.ar_commit = gt->gt_log_flush_secs;
	args.ar_quota_quantum = gt->gt_quota_quantum;
	if (gt->gt_statfs_slow)
		args.ar_statfs_quantum = 0;
	else
		args.ar_statfs_quantum = gt->gt_statfs_quantum;
	spin_unlock(&gt->gt_spin);
	error = gfs2_mount_args(&args, data);
	if (error)
		return error;

	/* Not allowed to change locking details */
	if (strcmp(args.ar_lockproto, sdp->sd_args.ar_lockproto) ||
	    strcmp(args.ar_locktable, sdp->sd_args.ar_locktable) ||
	    strcmp(args.ar_hostdata, sdp->sd_args.ar_hostdata))
		return -EINVAL;

	/* Some flags must not be changed */
	if (args_neq(&args, &sdp->sd_args, spectator) ||
	    args_neq(&args, &sdp->sd_args, ignore_local_fs) ||
	    args_neq(&args, &sdp->sd_args, localflocks) ||
	    args_neq(&args, &sdp->sd_args, localcaching) ||
	    args_neq(&args, &sdp->sd_args, meta))
		return -EINVAL;

	if (sdp->sd_args.ar_spectator)
		*flags |= MS_RDONLY;

	if ((sb->s_flags ^ *flags) & MS_RDONLY) {
		if (*flags & MS_RDONLY)
			error = gfs2_make_fs_ro(sdp);
		else
			error = gfs2_make_fs_rw(sdp);
		if (error)
			return error;
	}

	sdp->sd_args = args;
	if (sdp->sd_args.ar_posix_acl)
		sb->s_flags |= MS_POSIXACL;
	else
		sb->s_flags &= ~MS_POSIXACL;
	if (sdp->sd_args.ar_nobarrier)
		set_bit(SDF_NOBARRIERS, &sdp->sd_flags);
	else
		clear_bit(SDF_NOBARRIERS, &sdp->sd_flags);
	spin_lock(&gt->gt_spin);
	gt->gt_log_flush_secs = args.ar_commit;
	gt->gt_quota_quantum = args.ar_quota_quantum;
	if (args.ar_statfs_quantum) {
		gt->gt_statfs_slow = 0;
		gt->gt_statfs_quantum = args.ar_statfs_quantum;
	}
	else {
		gt->gt_statfs_slow = 1;
		gt->gt_statfs_quantum = 30;
	}
	spin_unlock(&gt->gt_spin);

	gfs2_online_uevent(sdp);
	return 0;
}