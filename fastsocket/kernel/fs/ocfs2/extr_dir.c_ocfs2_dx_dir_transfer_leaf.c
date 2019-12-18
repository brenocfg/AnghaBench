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
typedef  scalar_t__ u32 ;
struct ocfs2_dx_entry_list {struct ocfs2_dx_entry* de_entries; int /*<<< orphan*/  de_num_used; } ;
struct ocfs2_dx_leaf {struct ocfs2_dx_entry_list dl_list; } ;
struct ocfs2_dx_entry {int /*<<< orphan*/  dx_major_hash; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ocfs2_dx_leaf*,struct ocfs2_dx_leaf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_dx_entry**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_dx_dir_leaf_insert_tail (struct ocfs2_dx_leaf*,struct ocfs2_dx_entry*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static void ocfs2_dx_dir_transfer_leaf(struct inode *dir, u32 split_hash,
				       handle_t *handle,
				       struct ocfs2_dx_leaf *tmp_dx_leaf,
				       struct buffer_head **orig_dx_leaves,
				       struct buffer_head **new_dx_leaves,
				       int num_dx_leaves)
{
	int i, j, num_used;
	u32 major_hash;
	struct ocfs2_dx_leaf *orig_dx_leaf, *new_dx_leaf;
	struct ocfs2_dx_entry_list *orig_list, *new_list, *tmp_list;
	struct ocfs2_dx_entry *dx_entry;

	tmp_list = &tmp_dx_leaf->dl_list;

	for (i = 0; i < num_dx_leaves; i++) {
		orig_dx_leaf = (struct ocfs2_dx_leaf *) orig_dx_leaves[i]->b_data;
		orig_list = &orig_dx_leaf->dl_list;
		new_dx_leaf = (struct ocfs2_dx_leaf *) new_dx_leaves[i]->b_data;
		new_list = &new_dx_leaf->dl_list;

		num_used = le16_to_cpu(orig_list->de_num_used);

		memcpy(tmp_dx_leaf, orig_dx_leaf, dir->i_sb->s_blocksize);
		tmp_list->de_num_used = cpu_to_le16(0);
		memset(&tmp_list->de_entries, 0, sizeof(*dx_entry)*num_used);

		for (j = 0; j < num_used; j++) {
			dx_entry = &orig_list->de_entries[j];
			major_hash = le32_to_cpu(dx_entry->dx_major_hash);
			if (major_hash >= split_hash)
				ocfs2_dx_dir_leaf_insert_tail(new_dx_leaf,
							      dx_entry);
			else
				ocfs2_dx_dir_leaf_insert_tail(tmp_dx_leaf,
							      dx_entry);
		}
		memcpy(orig_dx_leaf, tmp_dx_leaf, dir->i_sb->s_blocksize);

		ocfs2_journal_dirty(handle, orig_dx_leaves[i]);
		ocfs2_journal_dirty(handle, new_dx_leaves[i]);
	}
}