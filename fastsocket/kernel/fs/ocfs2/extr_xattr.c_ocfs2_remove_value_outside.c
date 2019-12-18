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
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  dealloc; int /*<<< orphan*/ * meta_ac; int /*<<< orphan*/  handle; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct ocfs2_xattr_header {struct ocfs2_xattr_entry* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_name_offset; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_caching_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int OCFS2_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (int /*<<< orphan*/ *) ; 
 int ocfs2_lock_xattr_remove_allocators (struct inode*,struct ocfs2_xattr_value_root*,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ ocfs2_remove_extent_credits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_start_trans (struct ocfs2_super*,scalar_t__) ; 
 scalar_t__ ocfs2_xattr_is_local (struct ocfs2_xattr_entry*) ; 
 int ocfs2_xattr_value_truncate (struct inode*,struct ocfs2_xattr_value_buf*,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*) ; 

__attribute__((used)) static int ocfs2_remove_value_outside(struct inode*inode,
				      struct ocfs2_xattr_value_buf *vb,
				      struct ocfs2_xattr_header *header,
				      struct ocfs2_caching_info *ref_ci,
				      struct buffer_head *ref_root_bh)
{
	int ret = 0, i, ref_credits;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_xattr_set_ctxt ctxt = { NULL, NULL, };
	void *val;

	ocfs2_init_dealloc_ctxt(&ctxt.dealloc);

	for (i = 0; i < le16_to_cpu(header->xh_count); i++) {
		struct ocfs2_xattr_entry *entry = &header->xh_entries[i];

		if (ocfs2_xattr_is_local(entry))
			continue;

		val = (void *)header +
			le16_to_cpu(entry->xe_name_offset);
		vb->vb_xv = (struct ocfs2_xattr_value_root *)
			(val + OCFS2_XATTR_SIZE(entry->xe_name_len));

		ret = ocfs2_lock_xattr_remove_allocators(inode, vb->vb_xv,
							 ref_ci, ref_root_bh,
							 &ctxt.meta_ac,
							 &ref_credits);

		ctxt.handle = ocfs2_start_trans(osb, ref_credits +
					ocfs2_remove_extent_credits(osb->sb));
		if (IS_ERR(ctxt.handle)) {
			ret = PTR_ERR(ctxt.handle);
			mlog_errno(ret);
			break;
		}

		ret = ocfs2_xattr_value_truncate(inode, vb, 0, &ctxt);
		if (ret < 0) {
			mlog_errno(ret);
			break;
		}

		ocfs2_commit_trans(osb, ctxt.handle);
		if (ctxt.meta_ac) {
			ocfs2_free_alloc_context(ctxt.meta_ac);
			ctxt.meta_ac = NULL;
		}
	}

	if (ctxt.meta_ac)
		ocfs2_free_alloc_context(ctxt.meta_ac);
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &ctxt.dealloc);
	return ret;
}