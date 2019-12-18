#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct extent_io_tree {int dummy; } ;
struct TYPE_6__ {struct extent_io_tree io_tree; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int PF_MEMALLOC ; 
 int /*<<< orphan*/  btrfs_get_extent ; 
 TYPE_2__* current ; 
 int extent_write_full_page (struct extent_io_tree*,struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int btrfs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct extent_io_tree *tree;


	if (current->flags & PF_MEMALLOC) {
		redirty_page_for_writepage(wbc, page);
		unlock_page(page);
		return 0;
	}
	tree = &BTRFS_I(page->mapping->host)->io_tree;
	return extent_write_full_page(tree, page, btrfs_get_extent, wbc);
}