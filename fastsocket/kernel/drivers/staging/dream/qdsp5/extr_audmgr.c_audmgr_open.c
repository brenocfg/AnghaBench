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
struct audmgr {scalar_t__ state; int /*<<< orphan*/ * ept; int /*<<< orphan*/ * task; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDMGR_PROG ; 
 int /*<<< orphan*/  AUDMGR_VERS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSM_RPC_UNINTERRUPTIBLE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ STATE_CLOSED ; 
 scalar_t__ STATE_DISABLED ; 
 int /*<<< orphan*/  audmgr_rpc_thread ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct audmgr*,char*) ; 
 int /*<<< orphan*/  msm_rpc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msm_rpc_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int audmgr_open(struct audmgr *am)
{
	int rc;

	if (am->state != STATE_CLOSED)
		return 0;

	am->ept = msm_rpc_connect(AUDMGR_PROG,
				AUDMGR_VERS,
				MSM_RPC_UNINTERRUPTIBLE);

	init_waitqueue_head(&am->wait);

	if (IS_ERR(am->ept)) {
		rc = PTR_ERR(am->ept);
		am->ept = NULL;
		pr_err("audmgr: failed to connect to audmgr svc\n");
		return rc;
	}

	am->task = kthread_run(audmgr_rpc_thread, am, "audmgr_rpc");
	if (IS_ERR(am->task)) {
		rc = PTR_ERR(am->task);
		am->task = NULL;
		msm_rpc_close(am->ept);
		am->ept = NULL;
		return rc;
	}

	am->state = STATE_DISABLED;
	return 0;
}