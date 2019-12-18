#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ocfs2_xattr_reflink {int /*<<< orphan*/  old_inode; int /*<<< orphan*/  new_inode; } ;
struct ocfs2_reflink_xattr_tree_args {void* new_bucket; void* old_bucket; struct buffer_head* new_blk_bh; struct buffer_head* old_blk_bh; struct ocfs2_xattr_reflink* reflink; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  para ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memset (struct ocfs2_reflink_xattr_tree_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_iterate_xattr_index_block (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ,struct ocfs2_reflink_xattr_tree_args*) ; 
 int /*<<< orphan*/  ocfs2_reflink_xattr_rec ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_free (void*) ; 
 void* ocfs2_xattr_bucket_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_reflink_xattr_tree(struct ocfs2_xattr_reflink *args,
				    struct buffer_head *blk_bh,
				    struct buffer_head *new_blk_bh)
{
	int ret;
	struct ocfs2_reflink_xattr_tree_args para;

	memset(&para, 0, sizeof(para));
	para.reflink = args;
	para.old_blk_bh = blk_bh;
	para.new_blk_bh = new_blk_bh;

	para.old_bucket = ocfs2_xattr_bucket_new(args->old_inode);
	if (!para.old_bucket) {
		mlog_errno(-ENOMEM);
		return -ENOMEM;
	}

	para.new_bucket = ocfs2_xattr_bucket_new(args->new_inode);
	if (!para.new_bucket) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_iterate_xattr_index_block(args->old_inode, blk_bh,
					      ocfs2_reflink_xattr_rec,
					      &para);
	if (ret)
		mlog_errno(ret);

out:
	ocfs2_xattr_bucket_free(para.old_bucket);
	ocfs2_xattr_bucket_free(para.new_bucket);
	return ret;
}