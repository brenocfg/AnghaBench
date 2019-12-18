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
struct TYPE_13__ {int error; } ;
struct TYPE_14__ {TYPE_6__ h; } ;
struct TYPE_10__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {int numargs; TYPE_4__* args; TYPE_3__ h; } ;
struct fuse_req {int force; TYPE_7__ out; TYPE_5__ in; } ;
struct fuse_flush_in {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_flush; } ;
struct TYPE_9__ {TYPE_1__* dentry; } ;
struct file {struct fuse_file* private_data; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  inarg ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_11__ {int size; struct fuse_flush_in* value; } ;
struct TYPE_8__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_FLUSH ; 
 struct fuse_req* fuse_get_req_nofail_nopages (struct fuse_conn*,struct file*) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_flush_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fuse_flush(struct file *file, fl_owner_t id)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	struct fuse_req *req;
	struct fuse_flush_in inarg;
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	if (fc->no_flush)
		return 0;

	req = fuse_get_req_nofail_nopages(fc, file);
	memset(&inarg, 0, sizeof(inarg));
	inarg.fh = ff->fh;
	inarg.lock_owner = fuse_lock_owner_id(fc, id);
	req->in.h.opcode = FUSE_FLUSH;
	req->in.h.nodeid = get_node_id(inode);
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	req->force = 1;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (err == -ENOSYS) {
		fc->no_flush = 1;
		err = 0;
	}
	return err;
}