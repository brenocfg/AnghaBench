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
struct ocfs2_xattr_set_ctxt {struct ocfs2_alloc_context* data_ac; struct ocfs2_alloc_context* meta_ac; int /*<<< orphan*/ * handle; } ;
struct ocfs2_xattr_search {int /*<<< orphan*/  bucket; int /*<<< orphan*/  xattr_bh; scalar_t__ not_found; struct buffer_head* inode_bh; } ;
struct ocfs2_xattr_info {int name_index; char const* name; void const* value; size_t value_len; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_xattr_sem; } ;
struct TYPE_3__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ENODATA ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 scalar_t__ OCFS2_MIN_BLOCKSIZE ; 
 int /*<<< orphan*/  OCFS2_SB (TYPE_1__*) ; 
 int __ocfs2_xattr_set_handle (struct inode*,struct ocfs2_dinode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_supports_xattr (int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_block_find (struct inode*,int,char const*,struct ocfs2_xattr_search*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_new (struct inode*) ; 
 int ocfs2_xattr_ibody_find (struct inode*,int,char const*,struct ocfs2_xattr_search*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ocfs2_xattr_set_handle(handle_t *handle,
			   struct inode *inode,
			   struct buffer_head *di_bh,
			   int name_index,
			   const char *name,
			   const void *value,
			   size_t value_len,
			   int flags,
			   struct ocfs2_alloc_context *meta_ac,
			   struct ocfs2_alloc_context *data_ac)
{
	struct ocfs2_dinode *di;
	int ret;

	struct ocfs2_xattr_info xi = {
		.name_index = name_index,
		.name = name,
		.value = value,
		.value_len = value_len,
	};

	struct ocfs2_xattr_search xis = {
		.not_found = -ENODATA,
	};

	struct ocfs2_xattr_search xbs = {
		.not_found = -ENODATA,
	};

	struct ocfs2_xattr_set_ctxt ctxt = {
		.handle = handle,
		.meta_ac = meta_ac,
		.data_ac = data_ac,
	};

	if (!ocfs2_supports_xattr(OCFS2_SB(inode->i_sb)))
		return -EOPNOTSUPP;

	/*
	 * In extreme situation, may need xattr bucket when
	 * block size is too small. And we have already reserved
	 * the credits for bucket in mknod.
	 */
	if (inode->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE) {
		xbs.bucket = ocfs2_xattr_bucket_new(inode);
		if (!xbs.bucket) {
			mlog_errno(-ENOMEM);
			return -ENOMEM;
		}
	}

	xis.inode_bh = xbs.inode_bh = di_bh;
	di = (struct ocfs2_dinode *)di_bh->b_data;

	down_write(&OCFS2_I(inode)->ip_xattr_sem);

	ret = ocfs2_xattr_ibody_find(inode, name_index, name, &xis);
	if (ret)
		goto cleanup;
	if (xis.not_found) {
		ret = ocfs2_xattr_block_find(inode, name_index, name, &xbs);
		if (ret)
			goto cleanup;
	}

	ret = __ocfs2_xattr_set_handle(inode, di, &xi, &xis, &xbs, &ctxt);

cleanup:
	up_write(&OCFS2_I(inode)->ip_xattr_sem);
	brelse(xbs.xattr_bh);
	ocfs2_xattr_bucket_free(xbs.bucket);

	return ret;
}