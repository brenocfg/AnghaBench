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
struct svc_rqst {int dummy; } ;
struct nlm_res {int /*<<< orphan*/  status; int /*<<< orphan*/  cookie; } ;
struct nlm_host {int dummy; } ;
struct nlm_file {int dummy; } ;
struct nlm_args {int /*<<< orphan*/  lock; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cast_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ locks_in_grace () ; 
 int /*<<< orphan*/  nlm_drop_reply ; 
 int /*<<< orphan*/  nlm_lck_denied_grace_period ; 
 int /*<<< orphan*/  nlm_release_file (struct nlm_file*) ; 
 int /*<<< orphan*/  nlm_release_host (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmsvc_retrieve_args (struct svc_rqst*,struct nlm_args*,struct nlm_host**,struct nlm_file**) ; 
 int /*<<< orphan*/  nlmsvc_unlock (struct nlm_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_drop_reply ; 
 int /*<<< orphan*/  rpc_success ; 

__attribute__((used)) static __be32
nlmsvc_proc_unlock(struct svc_rqst *rqstp, struct nlm_args *argp,
				           struct nlm_res  *resp)
{
	struct nlm_host	*host;
	struct nlm_file	*file;

	dprintk("lockd: UNLOCK        called\n");

	resp->cookie = argp->cookie;

	/* Don't accept new lock requests during grace period */
	if (locks_in_grace()) {
		resp->status = nlm_lck_denied_grace_period;
		return rpc_success;
	}

	/* Obtain client and file */
	if ((resp->status = nlmsvc_retrieve_args(rqstp, argp, &host, &file)))
		return resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Now try to remove the lock */
	resp->status = cast_status(nlmsvc_unlock(file, &argp->lock));

	dprintk("lockd: UNLOCK        status %d\n", ntohl(resp->status));
	nlm_release_host(host);
	nlm_release_file(file);
	return rpc_success;
}