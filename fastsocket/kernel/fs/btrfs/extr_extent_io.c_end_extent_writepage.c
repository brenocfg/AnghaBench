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
typedef  int /*<<< orphan*/  u64 ;
struct page {TYPE_1__* mapping; } ;
struct extent_io_tree {TYPE_2__* ops; } ;
struct TYPE_6__ {struct extent_io_tree io_tree; } ;
struct TYPE_5__ {int (* writepage_end_io_hook ) (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int stub1 (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int end_extent_writepage(struct page *page, int err, u64 start, u64 end)
{
	int uptodate = (err == 0);
	struct extent_io_tree *tree;
	int ret;

	tree = &BTRFS_I(page->mapping->host)->io_tree;

	if (tree->ops && tree->ops->writepage_end_io_hook) {
		ret = tree->ops->writepage_end_io_hook(page, start,
					       end, NULL, uptodate);
		if (ret)
			uptodate = 0;
	}

	if (!uptodate) {
		ClearPageUptodate(page);
		SetPageError(page);
	}
	return 0;
}