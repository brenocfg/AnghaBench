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
struct TYPE_3__ {scalar_t__ status; } ;
struct TYPE_4__ {int block; } ;
struct nlm_rqst {TYPE_1__ a_res; int /*<<< orphan*/  a_count; TYPE_2__ a_args; int /*<<< orphan*/  a_flags; } ;
struct nlm_host {int dummy; } ;
struct file_lock {int /*<<< orphan*/  fl_file; } ;

/* Variables and functions */
 int ENOLCK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NLMPROC_CANCEL ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  nfs_file_cred (int /*<<< orphan*/ ) ; 
 struct nlm_rqst* nlm_alloc_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_get_host (struct nlm_host*) ; 
 scalar_t__ nlm_lck_denied ; 
 int /*<<< orphan*/  nlm_release_call (struct nlm_rqst*) ; 
 int nlmclnt_async_call (int /*<<< orphan*/ ,struct nlm_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmclnt_cancel_ops ; 
 int /*<<< orphan*/  nlmclnt_setlockargs (struct nlm_rqst*,struct file_lock*) ; 

__attribute__((used)) static int nlmclnt_cancel(struct nlm_host *host, int block, struct file_lock *fl)
{
	struct nlm_rqst	*req;
	int status;

	dprintk("lockd: blocking lock attempt was interrupted by a signal.\n"
		"       Attempting to cancel lock.\n");

	req = nlm_alloc_call(nlm_get_host(host));
	if (!req)
		return -ENOMEM;
	req->a_flags = RPC_TASK_ASYNC;

	nlmclnt_setlockargs(req, fl);
	req->a_args.block = block;

	atomic_inc(&req->a_count);
	status = nlmclnt_async_call(nfs_file_cred(fl->fl_file), req,
			NLMPROC_CANCEL, &nlmclnt_cancel_ops);
	if (status == 0 && req->a_res.status == nlm_lck_denied)
		status = -ENOLCK;
	nlm_release_call(req);
	return status;
}