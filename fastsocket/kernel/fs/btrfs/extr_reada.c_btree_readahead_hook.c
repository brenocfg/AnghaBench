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
struct extent_buffer {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int __readahead_hook (struct btrfs_root*,struct extent_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reada_start_machine (int /*<<< orphan*/ ) ; 

int btree_readahead_hook(struct btrfs_root *root, struct extent_buffer *eb,
			 u64 start, int err)
{
	int ret;

	ret = __readahead_hook(root, eb, start, err);

	reada_start_machine(root->fs_info);

	return ret;
}