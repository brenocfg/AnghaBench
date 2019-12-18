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
struct writeback_control {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_2__ {struct extent_io_tree io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_get_extent ; 
 int extent_writepages (struct extent_io_tree*,struct address_space*,int /*<<< orphan*/ ,struct writeback_control*) ; 

int btrfs_writepages(struct address_space *mapping,
		     struct writeback_control *wbc)
{
	struct extent_io_tree *tree;

	tree = &BTRFS_I(mapping->host)->io_tree;
	return extent_writepages(tree, mapping, btrfs_get_extent, wbc);
}