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
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; scalar_t__ bg_bitmap; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ b_committed_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_GROUP_DESC (struct ocfs2_group_desc*) ; 
 int OCFS2_JOURNAL_ACCESS_UNDO ; 
 int OCFS2_JOURNAL_ACCESS_WRITE ; 
 TYPE_1__* bh2jh (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_bit (unsigned int,unsigned long*) ; 
 scalar_t__ ocfs2_is_cluster_bitmap (struct inode*) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static inline int ocfs2_block_group_clear_bits(handle_t *handle,
					       struct inode *alloc_inode,
					       struct ocfs2_group_desc *bg,
					       struct buffer_head *group_bh,
					       unsigned int bit_off,
					       unsigned int num_bits)
{
	int status;
	unsigned int tmp;
	int journal_type = OCFS2_JOURNAL_ACCESS_WRITE;
	struct ocfs2_group_desc *undo_bg = NULL;
	int cluster_bitmap = 0;

	mlog_entry_void();

	/* The caller got this descriptor from
	 * ocfs2_read_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));

	mlog(0, "off = %u, num = %u\n", bit_off, num_bits);

	if (ocfs2_is_cluster_bitmap(alloc_inode))
		journal_type = OCFS2_JOURNAL_ACCESS_UNDO;

	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 group_bh, journal_type);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	if (ocfs2_is_cluster_bitmap(alloc_inode))
		cluster_bitmap = 1;

	if (cluster_bitmap) {
		jbd_lock_bh_state(group_bh);
		undo_bg = (struct ocfs2_group_desc *)
					bh2jh(group_bh)->b_committed_data;
		BUG_ON(!undo_bg);
	}

	tmp = num_bits;
	while(tmp--) {
		ocfs2_clear_bit((bit_off + tmp),
				(unsigned long *) bg->bg_bitmap);
		if (cluster_bitmap)
			ocfs2_set_bit(bit_off + tmp,
				      (unsigned long *) undo_bg->bg_bitmap);
	}
	le16_add_cpu(&bg->bg_free_bits_count, num_bits);

	if (cluster_bitmap)
		jbd_unlock_bh_state(group_bh);

	status = ocfs2_journal_dirty(handle, group_bh);
	if (status < 0)
		mlog_errno(status);
bail:
	return status;
}