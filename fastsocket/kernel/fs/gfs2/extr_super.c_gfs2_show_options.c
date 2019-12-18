#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int /*<<< orphan*/  mnt_root; TYPE_1__* mnt_sb; } ;
struct seq_file {int dummy; } ;
struct TYPE_4__ {int gt_log_flush_secs; int gt_statfs_quantum; int gt_quota_quantum; } ;
struct gfs2_args {int ar_quota; int ar_data; int ar_errors; int /*<<< orphan*/  ar_statfs_percent; scalar_t__ ar_discard; scalar_t__ ar_suiddir; scalar_t__ ar_posix_acl; scalar_t__ ar_upgrade; scalar_t__ ar_debug; scalar_t__ ar_localcaching; scalar_t__ ar_localflocks; scalar_t__ ar_ignore_local_fs; scalar_t__ ar_spectator; scalar_t__* ar_hostdata; scalar_t__* ar_locktable; scalar_t__* ar_lockproto; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; TYPE_2__ sd_tune; int /*<<< orphan*/  sd_master_dir; struct gfs2_args sd_args; } ;
struct TYPE_3__ {struct gfs2_sbd* s_fs_info; } ;

/* Variables and functions */
 int GFS2_DATA_DEFAULT ; 
#define  GFS2_DATA_ORDERED 134 
#define  GFS2_DATA_WRITEBACK 133 
 int GFS2_ERRORS_DEFAULT ; 
#define  GFS2_ERRORS_PANIC 132 
#define  GFS2_ERRORS_WITHDRAW 131 
#define  GFS2_QUOTA_ACCOUNT 130 
 int GFS2_QUOTA_DEFAULT ; 
#define  GFS2_QUOTA_OFF 129 
#define  GFS2_QUOTA_ON 128 
 int /*<<< orphan*/  SDF_DEMOTE ; 
 int /*<<< orphan*/  SDF_NOBARRIERS ; 
 scalar_t__ is_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_show_options(struct seq_file *s, struct vfsmount *mnt)
{
	struct gfs2_sbd *sdp = mnt->mnt_sb->s_fs_info;
	struct gfs2_args *args = &sdp->sd_args;
	int val;

	if (is_ancestor(mnt->mnt_root, sdp->sd_master_dir))
		seq_printf(s, ",meta");
	if (args->ar_lockproto[0])
		seq_printf(s, ",lockproto=%s", args->ar_lockproto);
	if (args->ar_locktable[0])
		seq_printf(s, ",locktable=%s", args->ar_locktable);
	if (args->ar_hostdata[0])
		seq_printf(s, ",hostdata=%s", args->ar_hostdata);
	if (args->ar_spectator)
		seq_printf(s, ",spectator");
	if (args->ar_ignore_local_fs)
		seq_printf(s, ",ignore_local_fs");
	if (args->ar_localflocks)
		seq_printf(s, ",localflocks");
	if (args->ar_localcaching)
		seq_printf(s, ",localcaching");
	if (args->ar_debug)
		seq_printf(s, ",debug");
	if (args->ar_upgrade)
		seq_printf(s, ",upgrade");
	if (args->ar_posix_acl)
		seq_printf(s, ",acl");
	if (args->ar_quota != GFS2_QUOTA_DEFAULT) {
		char *state;
		switch (args->ar_quota) {
		case GFS2_QUOTA_OFF:
			state = "off";
			break;
		case GFS2_QUOTA_ACCOUNT:
			state = "account";
			break;
		case GFS2_QUOTA_ON:
			state = "on";
			break;
		default:
			state = "unknown";
			break;
		}
		seq_printf(s, ",quota=%s", state);
	}
	if (args->ar_suiddir)
		seq_printf(s, ",suiddir");
	if (args->ar_data != GFS2_DATA_DEFAULT) {
		char *state;
		switch (args->ar_data) {
		case GFS2_DATA_WRITEBACK:
			state = "writeback";
			break;
		case GFS2_DATA_ORDERED:
			state = "ordered";
			break;
		default:
			state = "unknown";
			break;
		}
		seq_printf(s, ",data=%s", state);
	}
	if (args->ar_discard)
		seq_printf(s, ",discard");
	val = sdp->sd_tune.gt_log_flush_secs;
	if (val != 60)
		seq_printf(s, ",commit=%d", val);
	val = sdp->sd_tune.gt_statfs_quantum;
	if (val != 30)
		seq_printf(s, ",statfs_quantum=%d", val);
	val = sdp->sd_tune.gt_quota_quantum;
	if (val != 60)
		seq_printf(s, ",quota_quantum=%d", val);
	if (args->ar_statfs_percent)
		seq_printf(s, ",statfs_percent=%d", args->ar_statfs_percent);
	if (args->ar_errors != GFS2_ERRORS_DEFAULT) {
		const char *state;

		switch (args->ar_errors) {
		case GFS2_ERRORS_WITHDRAW:
			state = "withdraw";
			break;
		case GFS2_ERRORS_PANIC:
			state = "panic";
			break;
		default:
			state = "unknown";
			break;
		}
		seq_printf(s, ",errors=%s", state);
	}
	if (test_bit(SDF_NOBARRIERS, &sdp->sd_flags))
		seq_printf(s, ",nobarrier");
	if (test_bit(SDF_DEMOTE, &sdp->sd_flags))
		seq_printf(s, ",demote_interface_used");
	return 0;
}