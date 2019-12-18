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
struct ocfs2_xattr_value_root {int dummy; } ;
struct ocfs2_xattr_value_buf {struct ocfs2_xattr_value_root* vb_xv; } ;
struct ocfs2_xattr_header {struct ocfs2_xattr_entry* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_name_offset; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int OCFS2_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_value_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct ocfs2_xattr_value_buf*) ; 
 scalar_t__ ocfs2_xattr_is_local (struct ocfs2_xattr_entry*) ; 
 int ocfs2_xattr_value_attach_refcount (struct inode*,struct ocfs2_xattr_value_root*,struct ocfs2_extent_tree*,struct ocfs2_caching_info*,struct buffer_head*,struct ocfs2_cached_dealloc_ctxt*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_xattr_attach_refcount_normal(struct inode *inode,
				struct ocfs2_xattr_value_buf *vb,
				struct ocfs2_xattr_header *header,
				struct ocfs2_caching_info *ref_ci,
				struct buffer_head *ref_root_bh,
				struct ocfs2_cached_dealloc_ctxt *dealloc)
{

	struct ocfs2_xattr_entry *xe;
	struct ocfs2_xattr_value_root *xv;
	struct ocfs2_extent_tree et;
	int i, ret = 0;

	for (i = 0; i < le16_to_cpu(header->xh_count); i++) {
		xe = &header->xh_entries[i];

		if (ocfs2_xattr_is_local(xe))
			continue;

		xv = (struct ocfs2_xattr_value_root *)((void *)header +
			le16_to_cpu(xe->xe_name_offset) +
			OCFS2_XATTR_SIZE(xe->xe_name_len));

		vb->vb_xv = xv;
		ocfs2_init_xattr_value_extent_tree(&et, INODE_CACHE(inode), vb);

		ret = ocfs2_xattr_value_attach_refcount(inode, xv, &et,
							ref_ci, ref_root_bh,
							dealloc, NULL);
		if (ret) {
			mlog_errno(ret);
			break;
		}
	}

	return ret;
}