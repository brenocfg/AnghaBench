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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int btree_read_extent_buffer_pages (struct btrfs_root*,struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct extent_buffer* btrfs_find_create_tree_block (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct extent_buffer *read_tree_block(struct btrfs_root *root, u64 bytenr,
				      u32 blocksize, u64 parent_transid)
{
	struct extent_buffer *buf = NULL;
	int ret;

	buf = btrfs_find_create_tree_block(root, bytenr, blocksize);
	if (!buf)
		return NULL;

	ret = btree_read_extent_buffer_pages(root, buf, 0, parent_transid);
	return buf;

}