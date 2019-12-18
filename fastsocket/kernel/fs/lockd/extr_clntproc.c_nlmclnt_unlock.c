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
struct nlm_res {scalar_t__ status; } ;
struct nlm_rqst {int /*<<< orphan*/  a_count; struct nlm_res a_res; struct nlm_host* a_host; } ;
struct nlm_host {int /*<<< orphan*/  h_rwsem; } ;
struct file_lock {unsigned char fl_flags; int /*<<< orphan*/  fl_file; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOLCK ; 
 unsigned char FL_EXISTS ; 
 int /*<<< orphan*/  NLMPROC_UNLOCK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int do_vfs_lock (struct file_lock*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_file_cred (int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_granted ; 
 scalar_t__ nlm_lck_denied_nolocks ; 
 int /*<<< orphan*/  nlm_release_call (struct nlm_rqst*) ; 
 int nlmclnt_async_call (int /*<<< orphan*/ ,struct nlm_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmclnt_unlock_ops ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nlmclnt_unlock(struct nlm_rqst *req, struct file_lock *fl)
{
	struct nlm_host	*host = req->a_host;
	struct nlm_res	*resp = &req->a_res;
	int status;
	unsigned char fl_flags = fl->fl_flags;

	/*
	 * Note: the server is supposed to either grant us the unlock
	 * request, or to deny it with NLM_LCK_DENIED_GRACE_PERIOD. In either
	 * case, we want to unlock.
	 */
	fl->fl_flags |= FL_EXISTS;
	down_read(&host->h_rwsem);
	status = do_vfs_lock(fl);
	up_read(&host->h_rwsem);
	fl->fl_flags = fl_flags;
	if (status == -ENOENT) {
		status = 0;
		goto out;
	}

	atomic_inc(&req->a_count);
	status = nlmclnt_async_call(nfs_file_cred(fl->fl_file), req,
			NLMPROC_UNLOCK, &nlmclnt_unlock_ops);
	if (status < 0)
		goto out;

	if (resp->status == nlm_granted)
		goto out;

	if (resp->status != nlm_lck_denied_nolocks)
		printk("lockd: unexpected unlock status: %d\n", resp->status);
	/* What to do now? I'm out of my depth... */
	status = -ENOLCK;
out:
	nlm_release_call(req);
	return status;
}