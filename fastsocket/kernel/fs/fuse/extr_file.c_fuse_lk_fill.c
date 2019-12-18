#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_12__ {int opcode; int /*<<< orphan*/  nodeid; } ;
struct TYPE_14__ {int numargs; TYPE_6__* args; TYPE_5__ h; } ;
struct TYPE_11__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  type; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fuse_lk_in {int /*<<< orphan*/  lk_flags; TYPE_4__ lk; int /*<<< orphan*/  owner; int /*<<< orphan*/  fh; } ;
struct TYPE_10__ {struct fuse_lk_in lk_in; } ;
struct fuse_req {TYPE_7__ in; TYPE_3__ misc; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int dummy; } ;
struct file_lock {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_owner; } ;
struct TYPE_9__ {TYPE_1__* dentry; } ;
struct file {struct fuse_file* private_data; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_13__ {int size; struct fuse_lk_in* value; } ;
struct TYPE_8__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_LK_FLOCK ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 

__attribute__((used)) static void fuse_lk_fill(struct fuse_req *req, struct file *file,
			 const struct file_lock *fl, int opcode, pid_t pid,
			 int flock)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	struct fuse_lk_in *arg = &req->misc.lk_in;

	arg->fh = ff->fh;
	arg->owner = fuse_lock_owner_id(fc, fl->fl_owner);
	arg->lk.start = fl->fl_start;
	arg->lk.end = fl->fl_end;
	arg->lk.type = fl->fl_type;
	arg->lk.pid = pid;
	if (flock)
		arg->lk_flags |= FUSE_LK_FLOCK;
	req->in.h.opcode = opcode;
	req->in.h.nodeid = get_node_id(inode);
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(*arg);
	req->in.args[0].value = arg;
}