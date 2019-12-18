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
struct ocfs2_super {int /*<<< orphan*/  osb_debug_root; struct ocfs2_dlm_debug* osb_dlm_debug; } ;
struct ocfs2_dlm_debug {int /*<<< orphan*/  d_locking_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocfs2_dlm_debug_fops ; 
 int /*<<< orphan*/  ocfs2_get_dlm_debug (struct ocfs2_dlm_debug*) ; 

__attribute__((used)) static int ocfs2_dlm_init_debug(struct ocfs2_super *osb)
{
	int ret = 0;
	struct ocfs2_dlm_debug *dlm_debug = osb->osb_dlm_debug;

	dlm_debug->d_locking_state = debugfs_create_file("locking_state",
							 S_IFREG|S_IRUSR,
							 osb->osb_debug_root,
							 osb,
							 &ocfs2_dlm_debug_fops);
	if (!dlm_debug->d_locking_state) {
		ret = -EINVAL;
		mlog(ML_ERROR,
		     "Unable to create locking state debugfs file.\n");
		goto out;
	}

	ocfs2_get_dlm_debug(dlm_debug);
out:
	return ret;
}