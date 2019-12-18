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
typedef  int u64 ;
typedef  long u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_tree_block_info {int dummy; } ;
struct btrfs_extent_item {int dummy; } ;
struct btrfs_extent_inline_ref {int dummy; } ;

/* Variables and functions */
 int BTRFS_EXTENT_FLAG_TREE_BLOCK ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int btrfs_extent_flags (struct extent_buffer*,struct btrfs_extent_item*) ; 
 scalar_t__ btrfs_extent_inline_ref_size (int) ; 
 int btrfs_extent_inline_ref_type (struct extent_buffer*,struct btrfs_extent_inline_ref*) ; 

__attribute__((used)) static int __get_extent_inline_ref(unsigned long *ptr, struct extent_buffer *eb,
				struct btrfs_extent_item *ei, u32 item_size,
				struct btrfs_extent_inline_ref **out_eiref,
				int *out_type)
{
	unsigned long end;
	u64 flags;
	struct btrfs_tree_block_info *info;

	if (!*ptr) {
		/* first call */
		flags = btrfs_extent_flags(eb, ei);
		if (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) {
			info = (struct btrfs_tree_block_info *)(ei + 1);
			*out_eiref =
				(struct btrfs_extent_inline_ref *)(info + 1);
		} else {
			*out_eiref = (struct btrfs_extent_inline_ref *)(ei + 1);
		}
		*ptr = (unsigned long)*out_eiref;
		if ((void *)*ptr >= (void *)ei + item_size)
			return -ENOENT;
	}

	end = (unsigned long)ei + item_size;
	*out_eiref = (struct btrfs_extent_inline_ref *)*ptr;
	*out_type = btrfs_extent_inline_ref_type(eb, *out_eiref);

	*ptr += btrfs_extent_inline_ref_size(*out_type);
	WARN_ON(*ptr > end);
	if (*ptr == end)
		return 1; /* last */

	return 0;
}