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
struct ocfs2_super {int /*<<< orphan*/ * dc_task; struct ocfs2_cluster_connection* cconn; TYPE_1__ osb_orphan_scan; int /*<<< orphan*/  osb_nfs_sync_lockres; int /*<<< orphan*/  osb_rename_lockres; int /*<<< orphan*/  osb_super_lockres; scalar_t__ node_num; int /*<<< orphan*/  uuid_str; int /*<<< orphan*/  osb_cluster_stack; } ;
struct ocfs2_cluster_connection {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct ocfs2_super*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_cluster_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_super*,struct ocfs2_cluster_connection**) ; 
 int /*<<< orphan*/  ocfs2_cluster_disconnect (struct ocfs2_cluster_connection*,int /*<<< orphan*/ ) ; 
 int ocfs2_cluster_this_node (scalar_t__*) ; 
 int ocfs2_dlm_init_debug (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_dlm_shutdown_debug (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_do_node_down ; 
 int /*<<< orphan*/  ocfs2_downconvert_thread ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_nfs_sync_lock_res_init (int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_orphan_scan_lock_res_init (int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_rename_lock_res_init (int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_super_lock_res_init (int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int ocfs2_dlm_init(struct ocfs2_super *osb)
{
	int status = 0;
	struct ocfs2_cluster_connection *conn = NULL;

	mlog_entry_void();

	if (ocfs2_mount_local(osb)) {
		osb->node_num = 0;
		goto local;
	}

	status = ocfs2_dlm_init_debug(osb);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	/* launch downconvert thread */
	osb->dc_task = kthread_run(ocfs2_downconvert_thread, osb, "ocfs2dc");
	if (IS_ERR(osb->dc_task)) {
		status = PTR_ERR(osb->dc_task);
		osb->dc_task = NULL;
		mlog_errno(status);
		goto bail;
	}

	/* for now, uuid == domain */
	status = ocfs2_cluster_connect(osb->osb_cluster_stack,
				       osb->uuid_str,
				       strlen(osb->uuid_str),
				       ocfs2_do_node_down, osb,
				       &conn);
	if (status) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_cluster_this_node(&osb->node_num);
	if (status < 0) {
		mlog_errno(status);
		mlog(ML_ERROR,
		     "could not find this host's node number\n");
		ocfs2_cluster_disconnect(conn, 0);
		goto bail;
	}

local:
	ocfs2_super_lock_res_init(&osb->osb_super_lockres, osb);
	ocfs2_rename_lock_res_init(&osb->osb_rename_lockres, osb);
	ocfs2_nfs_sync_lock_res_init(&osb->osb_nfs_sync_lockres, osb);
	ocfs2_orphan_scan_lock_res_init(&osb->osb_orphan_scan.os_lockres, osb);

	osb->cconn = conn;

	status = 0;
bail:
	if (status < 0) {
		ocfs2_dlm_shutdown_debug(osb);
		if (osb->dc_task)
			kthread_stop(osb->dc_task);
	}

	mlog_exit(status);
	return status;
}