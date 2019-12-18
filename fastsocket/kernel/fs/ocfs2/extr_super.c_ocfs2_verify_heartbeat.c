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
struct ocfs2_super {int s_mount_opt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_MOUNT_HB_LOCAL ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_userspace_stack (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_verify_heartbeat(struct ocfs2_super *osb)
{
	if (ocfs2_mount_local(osb)) {
		if (osb->s_mount_opt & OCFS2_MOUNT_HB_LOCAL) {
			mlog(ML_ERROR, "Cannot heartbeat on a locally "
			     "mounted device.\n");
			return -EINVAL;
		}
	}

	if (ocfs2_userspace_stack(osb)) {
		if (osb->s_mount_opt & OCFS2_MOUNT_HB_LOCAL) {
			mlog(ML_ERROR, "Userspace stack expected, but "
			     "o2cb heartbeat arguments passed to mount\n");
			return -EINVAL;
		}
	}

	if (!(osb->s_mount_opt & OCFS2_MOUNT_HB_LOCAL)) {
		if (!ocfs2_mount_local(osb) && !ocfs2_is_hard_readonly(osb) &&
		    !ocfs2_userspace_stack(osb)) {
			mlog(ML_ERROR, "Heartbeat has to be started to mount "
			     "a read-write clustered device.\n");
			return -EINVAL;
		}
	}

	return 0;
}