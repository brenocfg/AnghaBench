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
struct extent_io_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_panic (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  tree_fs_info (struct extent_io_tree*) ; 

void extent_io_tree_panic(struct extent_io_tree *tree, int err)
{
	btrfs_panic(tree_fs_info(tree), err, "Locking error: "
		    "Extent tree was modified by another "
		    "thread while locked.");
}