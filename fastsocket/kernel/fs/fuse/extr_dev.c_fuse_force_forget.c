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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int numargs; TYPE_4__* args; TYPE_3__ h; } ;
struct fuse_req {scalar_t__ isreply; TYPE_5__ in; } ;
struct fuse_forget_in {int nlookup; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_9__ {int size; struct fuse_forget_in* value; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_FORGET ; 
 struct fuse_req* fuse_get_req_nofail_nopages (struct fuse_conn*,struct file*) ; 
 int /*<<< orphan*/  fuse_request_send_nowait (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_forget_in*,int /*<<< orphan*/ ,int) ; 

void fuse_force_forget(struct file *file, u64 nodeid)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	struct fuse_forget_in inarg;

	memset(&inarg, 0, sizeof(inarg));
	inarg.nlookup = 1;
	req = fuse_get_req_nofail_nopages(fc, file);
	req->in.h.opcode = FUSE_FORGET;
	req->in.h.nodeid = nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	req->isreply = 0;
	fuse_request_send_nowait(fc, req);
}