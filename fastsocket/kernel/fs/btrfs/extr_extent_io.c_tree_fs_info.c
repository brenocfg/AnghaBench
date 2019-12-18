#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct extent_io_tree {TYPE_2__* mapping; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct btrfs_fs_info *
tree_fs_info(struct extent_io_tree *tree)
{
	return btrfs_sb(tree->mapping->host->i_sb);
}