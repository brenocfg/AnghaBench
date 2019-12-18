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
struct inode {int dummy; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_10__ {TYPE_4__ h; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_5__ out; TYPE_3__ in; } ;
struct fuse_fsync_in {int fsync_flags; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_fsync; int no_fsyncdir; } ;
struct file {struct fuse_file* private_data; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_7__ {int size; struct fuse_fsync_in* value; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_FSYNC ; 
 int /*<<< orphan*/  FUSE_FSYNCDIR ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_sync_writes (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_fsync_in*,int /*<<< orphan*/ ,int) ; 
 int write_inode_now (struct inode*,int /*<<< orphan*/ ) ; 

int fuse_fsync_common(struct file *file, struct dentry *de, int datasync,
		      int isdir)
{
	struct inode *inode = de->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	struct fuse_req *req;
	struct fuse_fsync_in inarg;
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	if ((!isdir && fc->no_fsync) || (isdir && fc->no_fsyncdir))
		return 0;

	/*
	 * Start writeback against all dirty pages of the inode, then
	 * wait for all outstanding writes, before sending the FSYNC
	 * request.
	 */
	err = write_inode_now(inode, 0);
	if (err)
		return err;

	fuse_sync_writes(inode);

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return PTR_ERR(req);

	memset(&inarg, 0, sizeof(inarg));
	inarg.fh = ff->fh;
	inarg.fsync_flags = datasync ? 1 : 0;
	req->in.h.opcode = isdir ? FUSE_FSYNCDIR : FUSE_FSYNC;
	req->in.h.nodeid = get_node_id(inode);
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (err == -ENOSYS) {
		if (isdir)
			fc->no_fsyncdir = 1;
		else
			fc->no_fsync = 1;
		err = 0;
	}
	return err;
}