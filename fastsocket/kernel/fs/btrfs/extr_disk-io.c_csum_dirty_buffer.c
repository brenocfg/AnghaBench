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
typedef  scalar_t__ u64 ;
struct page {scalar_t__ private; TYPE_1__* mapping; scalar_t__ index; } ;
struct extent_io_tree {int dummy; } ;
struct extent_buffer {struct page** pages; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_4__ {struct extent_io_tree io_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ btrfs_header_bytenr (struct extent_buffer*) ; 
 int /*<<< orphan*/  csum_tree_block (struct btrfs_root*,struct extent_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csum_dirty_buffer(struct btrfs_root *root, struct page *page)
{
	struct extent_io_tree *tree;
	u64 start = (u64)page->index << PAGE_CACHE_SHIFT;
	u64 found_start;
	struct extent_buffer *eb;

	tree = &BTRFS_I(page->mapping->host)->io_tree;

	eb = (struct extent_buffer *)page->private;
	if (page != eb->pages[0])
		return 0;
	found_start = btrfs_header_bytenr(eb);
	if (found_start != start) {
		WARN_ON(1);
		return 0;
	}
	if (eb->pages[0] != page) {
		WARN_ON(1);
		return 0;
	}
	if (!PageUptodate(page)) {
		WARN_ON(1);
		return 0;
	}
	csum_tree_block(root, eb, 0);
	return 0;
}