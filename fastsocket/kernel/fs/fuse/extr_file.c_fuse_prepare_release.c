#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int opcode; int /*<<< orphan*/  nodeid; } ;
struct TYPE_10__ {int numargs; TYPE_4__* args; TYPE_3__ h; } ;
struct fuse_release_in {int flags; int /*<<< orphan*/  fh; } ;
struct TYPE_6__ {struct fuse_release_in in; } ;
struct TYPE_7__ {TYPE_1__ release; } ;
struct fuse_req {TYPE_5__ in; TYPE_2__ misc; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  polled_node; int /*<<< orphan*/  write_entry; struct fuse_req* reserved_req; struct fuse_conn* fc; } ;
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  polled_files; } ;
struct TYPE_9__ {int size; struct fuse_release_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_prepare_release(struct fuse_file *ff, int flags, int opcode)
{
	struct fuse_conn *fc = ff->fc;
	struct fuse_req *req = ff->reserved_req;
	struct fuse_release_in *inarg = &req->misc.release.in;

	spin_lock(&fc->lock);
	list_del(&ff->write_entry);
	if (!RB_EMPTY_NODE(&ff->polled_node))
		rb_erase(&ff->polled_node, &fc->polled_files);
	spin_unlock(&fc->lock);

	wake_up_interruptible_sync(&ff->poll_wait);

	inarg->fh = ff->fh;
	inarg->flags = flags;
	req->in.h.opcode = opcode;
	req->in.h.nodeid = ff->nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(struct fuse_release_in);
	req->in.args[0].value = inarg;
}