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
typedef  int /*<<< orphan*/  uid_t ;
struct rpc_clnt {int dummy; } ;
struct gss_upcall_msg {struct gss_auth* auth; int /*<<< orphan*/  uid; int /*<<< orphan*/  count; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  rpc_waitqueue; int /*<<< orphan*/  list; int /*<<< orphan*/  inode; } ;
struct gss_auth {TYPE_1__** dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct gss_upcall_msg* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int get_pipe_version () ; 
 int /*<<< orphan*/  gss_encode_msg (struct gss_upcall_msg*,struct rpc_clnt*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gss_upcall_msg*) ; 
 struct gss_upcall_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline struct gss_upcall_msg *
gss_alloc_msg(struct gss_auth *gss_auth, uid_t uid, struct rpc_clnt *clnt,
		int machine_cred)
{
	struct gss_upcall_msg *gss_msg;
	int vers;

	gss_msg = kzalloc(sizeof(*gss_msg), GFP_NOFS);
	if (gss_msg == NULL)
		return ERR_PTR(-ENOMEM);
	vers = get_pipe_version();
	if (vers < 0) {
		kfree(gss_msg);
		return ERR_PTR(vers);
	}
	gss_msg->inode = RPC_I(gss_auth->dentry[vers]->d_inode);
	INIT_LIST_HEAD(&gss_msg->list);
	rpc_init_wait_queue(&gss_msg->rpc_waitqueue, "RPCSEC_GSS upcall waitq");
	init_waitqueue_head(&gss_msg->waitqueue);
	atomic_set(&gss_msg->count, 1);
	gss_msg->uid = uid;
	gss_msg->auth = gss_auth;
	gss_encode_msg(gss_msg, clnt, machine_cred);
	return gss_msg;
}