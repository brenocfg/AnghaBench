#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  os_lockres; } ;
struct ocfs2_super {int /*<<< orphan*/ * cconn; TYPE_1__ osb_orphan_scan; int /*<<< orphan*/  osb_nfs_sync_lockres; int /*<<< orphan*/  osb_rename_lockres; int /*<<< orphan*/  osb_super_lockres; int /*<<< orphan*/ * dc_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_cluster_disconnect (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_dlm_shutdown_debug (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_drop_osb_locks (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 

void ocfs2_dlm_shutdown(struct ocfs2_super *osb,
			int hangup_pending)
{
	mlog_entry_void();

	ocfs2_drop_osb_locks(osb);

	/*
	 * Now that we have dropped all locks and ocfs2_dismount_volume()
	 * has disabled recovery, the DLM won't be talking to us.  It's
	 * safe to tear things down before disconnecting the cluster.
	 */

	if (osb->dc_task) {
		kthread_stop(osb->dc_task);
		osb->dc_task = NULL;
	}

	ocfs2_lock_res_free(&osb->osb_super_lockres);
	ocfs2_lock_res_free(&osb->osb_rename_lockres);
	ocfs2_lock_res_free(&osb->osb_nfs_sync_lockres);
	ocfs2_lock_res_free(&osb->osb_orphan_scan.os_lockres);

	ocfs2_cluster_disconnect(osb->cconn, hangup_pending);
	osb->cconn = NULL;

	ocfs2_dlm_shutdown_debug(osb);

	mlog_exit_void();
}