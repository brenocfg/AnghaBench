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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_10__ {TYPE_4__ h; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_5__ out; TYPE_3__ in; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; struct fuse_conn* fc; } ;
struct fuse_fallocate_in {int mode; scalar_t__ length; scalar_t__ offset; int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_fallocate; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_7__ {int size; struct fuse_fallocate_in* value; } ;

/* Variables and functions */
 int ENOSYS ; 
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int /*<<< orphan*/  FUSE_FALLOCATE ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_set_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,scalar_t__,scalar_t__) ; 

long fuse_file_fallocate(struct inode *inode, struct fuse_file *ff, int mode,
			 loff_t offset, loff_t length)
{
	struct fuse_conn *fc = ff->fc;
	struct fuse_req *req;
	struct fuse_fallocate_in inarg = {
		.fh = ff->fh,
		.offset = offset,
		.length = length,
		.mode = mode
	};
	int err;
	bool lock_inode = !(mode & FALLOC_FL_KEEP_SIZE) ||
			   (mode & FALLOC_FL_PUNCH_HOLE);

	if (fc->no_fallocate)
		return -EOPNOTSUPP;

	if (lock_inode) {
		mutex_lock(&inode->i_mutex);
		if (mode & FALLOC_FL_PUNCH_HOLE)
			fuse_set_nowrite(inode);
	}

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto out;
	}

	req->in.h.opcode = FUSE_FALLOCATE;
	req->in.h.nodeid = ff->nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	if (err == -ENOSYS) {
		fc->no_fallocate = 1;
		err = -EOPNOTSUPP;
	}
	fuse_put_request(fc, req);

	if (err)
		goto out;

	/* we could have extended the file */
	if (!(mode & FALLOC_FL_KEEP_SIZE))
		fuse_write_update_size(inode, offset + length);

	if (mode & FALLOC_FL_PUNCH_HOLE)
		truncate_pagecache_range(inode, offset, offset + length - 1);

	fuse_invalidate_attr(inode);

out:
	if (lock_inode) {
		if (mode & FALLOC_FL_PUNCH_HOLE)
			fuse_release_nowrite(inode);
		mutex_unlock(&inode->i_mutex);
	}

	return err;
}