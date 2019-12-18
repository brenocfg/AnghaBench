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
struct rpc_cred {int /*<<< orphan*/  cr_uid; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_4__ {int errno; } ;
struct gss_upcall_msg {int /*<<< orphan*/  waitqueue; TYPE_2__ msg; int /*<<< orphan*/ * ctx; TYPE_1__* inode; } ;
struct gss_cred {struct rpc_cred gc_base; } ;
struct gss_auth {int /*<<< orphan*/  client; } ;
struct TYPE_3__ {struct inode vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct gss_upcall_msg*) ; 
 int PTR_ERR (struct gss_upcall_msg*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_cred_set_ctx (struct rpc_cred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_msg (struct gss_upcall_msg*) ; 
 struct gss_upcall_msg* gss_setup_upcall (int /*<<< orphan*/ ,struct gss_auth*,struct rpc_cred*) ; 
 scalar_t__ pipe_version ; 
 int /*<<< orphan*/  pipe_version_waitqueue ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signalled () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  warn_gssd () ; 

__attribute__((used)) static inline int
gss_create_upcall(struct gss_auth *gss_auth, struct gss_cred *gss_cred)
{
	struct inode *inode;
	struct rpc_cred *cred = &gss_cred->gc_base;
	struct gss_upcall_msg *gss_msg;
	DEFINE_WAIT(wait);
	int err = 0;

	dprintk("RPC:       gss_upcall for uid %u\n", cred->cr_uid);
retry:
	gss_msg = gss_setup_upcall(gss_auth->client, gss_auth, cred);
	if (PTR_ERR(gss_msg) == -EAGAIN) {
		err = wait_event_interruptible_timeout(pipe_version_waitqueue,
				pipe_version >= 0, 15*HZ);
		if (err)
			goto out;
		if (pipe_version < 0)
			warn_gssd();
		goto retry;
	}
	if (IS_ERR(gss_msg)) {
		err = PTR_ERR(gss_msg);
		goto out;
	}
	inode = &gss_msg->inode->vfs_inode;
	for (;;) {
		prepare_to_wait(&gss_msg->waitqueue, &wait, TASK_INTERRUPTIBLE);
		spin_lock(&inode->i_lock);
		if (gss_msg->ctx != NULL || gss_msg->msg.errno < 0) {
			break;
		}
		spin_unlock(&inode->i_lock);
		if (signalled()) {
			err = -ERESTARTSYS;
			goto out_intr;
		}
		schedule();
	}
	if (gss_msg->ctx)
		gss_cred_set_ctx(cred, gss_msg->ctx);
	else
		err = gss_msg->msg.errno;
	spin_unlock(&inode->i_lock);
out_intr:
	finish_wait(&gss_msg->waitqueue, &wait);
	gss_release_msg(gss_msg);
out:
	dprintk("RPC:       gss_create_upcall for uid %u result %d\n",
			cred->cr_uid, err);
	return err;
}