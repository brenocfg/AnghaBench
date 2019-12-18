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
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int tree_mod_log_insert_move (struct btrfs_fs_info*,struct extent_buffer*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
tree_mod_log_eb_move(struct btrfs_fs_info *fs_info, struct extent_buffer *dst,
		     int dst_offset, int src_offset, int nr_items)
{
	int ret;
	ret = tree_mod_log_insert_move(fs_info, dst, dst_offset, src_offset,
				       nr_items, GFP_NOFS);
	BUG_ON(ret < 0);
}