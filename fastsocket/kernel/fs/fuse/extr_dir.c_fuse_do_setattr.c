#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_mode; scalar_t__ i_size; int /*<<< orphan*/  i_mapping; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_size; } ;
struct TYPE_15__ {int mode; scalar_t__ size; } ;
struct fuse_setattr_in {TYPE_7__ attr; int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  valid; int /*<<< orphan*/  fh; } ;
struct TYPE_13__ {int error; } ;
struct TYPE_14__ {int numargs; TYPE_5__ h; TYPE_4__* args; } ;
struct TYPE_9__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_6__ out; TYPE_3__ in; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int flags; int minor; int /*<<< orphan*/  lock; scalar_t__ atomic_o_trunc; } ;
struct fuse_attr_out {TYPE_7__ attr; int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  valid; int /*<<< orphan*/  fh; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  outarg ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_16__ {int /*<<< orphan*/  files; } ;
struct TYPE_12__ {int size; struct fuse_setattr_in* value; } ;
struct TYPE_10__ {int size; struct fuse_setattr_in* value; } ;

/* Variables and functions */
 int ATTR_OPEN ; 
 int ATTR_SIZE ; 
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  FATTR_FH ; 
 int /*<<< orphan*/  FATTR_LOCKOWNER ; 
 int FUSE_COMPAT_ATTR_OUT_SIZE ; 
 int FUSE_DEFAULT_PERMISSIONS ; 
 int /*<<< orphan*/  FUSE_SETATTR ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 int S_IFMT ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  __fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  attr_timeout (struct fuse_setattr_in*) ; 
 TYPE_8__* current ; 
 int /*<<< orphan*/  fuse_change_attributes_common (struct inode*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_set_nowrite (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  iattr_to_fattr (struct iattr*,struct fuse_setattr_in*) ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int inode_newsize_ok (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_setattr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__,scalar_t__) ; 

int fuse_do_setattr(struct inode *inode, struct iattr *attr,
		    struct file *file)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	struct fuse_setattr_in inarg;
	struct fuse_attr_out outarg;
	bool is_truncate = false;
	loff_t oldsize;
	int err;

	if (fc->flags & FUSE_DEFAULT_PERMISSIONS) {
		err = inode_change_ok(inode, attr);
		if (err)
			return err;
	}

	if ((attr->ia_valid & ATTR_OPEN) && fc->atomic_o_trunc)
		return 0;

	if (attr->ia_valid & ATTR_SIZE) {
		err = inode_newsize_ok(inode, attr->ia_size);
		if (err)
			return err;
		is_truncate = true;
	}

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return PTR_ERR(req);

	if (is_truncate)
		fuse_set_nowrite(inode);

	memset(&inarg, 0, sizeof(inarg));
	memset(&outarg, 0, sizeof(outarg));
	iattr_to_fattr(attr, &inarg);
	if (file) {
		struct fuse_file *ff = file->private_data;
		inarg.valid |= FATTR_FH;
		inarg.fh = ff->fh;
	}
	if (attr->ia_valid & ATTR_SIZE) {
		/* For mandatory locking in truncate */
		inarg.valid |= FATTR_LOCKOWNER;
		inarg.lock_owner = fuse_lock_owner_id(fc, current->files);
	}
	req->in.h.opcode = FUSE_SETATTR;
	req->in.h.nodeid = get_node_id(inode);
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	req->out.numargs = 1;
	if (fc->minor < 9)
		req->out.args[0].size = FUSE_COMPAT_ATTR_OUT_SIZE;
	else
		req->out.args[0].size = sizeof(outarg);
	req->out.args[0].value = &outarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (err) {
		if (err == -EINTR)
			fuse_invalidate_attr(inode);
		goto error;
	}

	if ((inode->i_mode ^ outarg.attr.mode) & S_IFMT) {
		make_bad_inode(inode);
		err = -EIO;
		goto error;
	}

	spin_lock(&fc->lock);
	fuse_change_attributes_common(inode, &outarg.attr,
				      attr_timeout(&outarg));
	oldsize = inode->i_size;
	i_size_write(inode, outarg.attr.size);

	if (is_truncate) {
		/* NOTE: this may release/reacquire fc->lock */
		__fuse_release_nowrite(inode);
	}
	spin_unlock(&fc->lock);

	/*
	 * Only call invalidate_inode_pages2() after removing
	 * FUSE_NOWRITE, otherwise fuse_launder_page() would deadlock.
	 */
	if (S_ISREG(inode->i_mode) && oldsize != outarg.attr.size) {
		truncate_pagecache(inode, oldsize, outarg.attr.size);
		invalidate_inode_pages2(inode->i_mapping);
	}

	return 0;

error:
	if (is_truncate)
		fuse_release_nowrite(inode);

	return err;
}