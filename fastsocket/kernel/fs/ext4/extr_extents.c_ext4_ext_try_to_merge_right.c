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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct ext4_extent_header {scalar_t__ eh_entries; } ;
struct ext4_extent {int /*<<< orphan*/  ee_len; } ;
struct ext4_ext_path {struct ext4_extent_header* p_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct ext4_extent* EXT_LAST_EXTENT (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  ext4_can_extents_be_merged (struct inode*,struct ext4_extent*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_is_uninitialized (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_mark_uninitialized (struct ext4_extent*) ; 
 unsigned int ext_depth (struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (struct ext4_extent*,struct ext4_extent*,unsigned int) ; 

__attribute__((used)) static int ext4_ext_try_to_merge_right(struct inode *inode,
			  struct ext4_ext_path *path,
			  struct ext4_extent *ex)
{
	struct ext4_extent_header *eh;
	unsigned int depth, len;
	int merge_done = 0;
	int uninitialized = 0;

	depth = ext_depth(inode);
	BUG_ON(path[depth].p_hdr == NULL);
	eh = path[depth].p_hdr;

	while (ex < EXT_LAST_EXTENT(eh)) {
		if (!ext4_can_extents_be_merged(inode, ex, ex + 1))
			break;
		/* merge with next extent! */
		if (ext4_ext_is_uninitialized(ex))
			uninitialized = 1;
		ex->ee_len = cpu_to_le16(ext4_ext_get_actual_len(ex)
				+ ext4_ext_get_actual_len(ex + 1));
		if (uninitialized)
			ext4_ext_mark_uninitialized(ex);

		if (ex + 1 < EXT_LAST_EXTENT(eh)) {
			len = (EXT_LAST_EXTENT(eh) - ex - 1)
				* sizeof(struct ext4_extent);
			memmove(ex + 1, ex + 2, len);
		}
		le16_add_cpu(&eh->eh_entries, -1);
		merge_done = 1;
		WARN_ON(eh->eh_entries == 0);
		if (!eh->eh_entries)
			ext4_error(inode->i_sb,
				   "inode#%lu, eh->eh_entries = 0!",
				   inode->i_ino);
	}

	return merge_done;
}