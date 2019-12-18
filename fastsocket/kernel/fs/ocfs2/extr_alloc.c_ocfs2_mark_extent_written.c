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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  OCFS2_EXT_UNWRITTEN ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_change_extent_flag (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_et_extent_map_truncate (struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_writes_unwritten_extents (int /*<<< orphan*/ ) ; 

int ocfs2_mark_extent_written(struct inode *inode,
			      struct ocfs2_extent_tree *et,
			      handle_t *handle, u32 cpos, u32 len, u32 phys,
			      struct ocfs2_alloc_context *meta_ac,
			      struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret;

	mlog(0, "Inode %lu cpos %u, len %u, phys clusters %u\n",
	     inode->i_ino, cpos, len, phys);

	if (!ocfs2_writes_unwritten_extents(OCFS2_SB(inode->i_sb))) {
		ocfs2_error(inode->i_sb, "Inode %llu has unwritten extents "
			    "that are being written to, but the feature bit "
			    "is not set in the super block.",
			    (unsigned long long)OCFS2_I(inode)->ip_blkno);
		ret = -EROFS;
		goto out;
	}

	/*
	 * XXX: This should be fixed up so that we just re-insert the
	 * next extent records.
	 */
	ocfs2_et_extent_map_truncate(et, 0);

	ret = ocfs2_change_extent_flag(handle, et, cpos,
				       len, phys, meta_ac, dealloc,
				       0, OCFS2_EXT_UNWRITTEN);
	if (ret)
		mlog_errno(ret);

out:
	return ret;
}