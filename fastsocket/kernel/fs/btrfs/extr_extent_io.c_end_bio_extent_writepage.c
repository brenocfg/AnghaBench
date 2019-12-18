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
typedef  int u64 ;
struct page {int /*<<< orphan*/  flags; scalar_t__ index; TYPE_1__* mapping; } ;
struct extent_io_tree {int dummy; } ;
struct bio_vec {int bv_offset; int bv_len; struct page* bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; } ;
struct TYPE_4__ {struct extent_io_tree io_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  check_page_writeback (struct extent_io_tree*,struct page*) ; 
 scalar_t__ end_extent_writepage (struct page*,int,int,int) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void end_bio_extent_writepage(struct bio *bio, int err)
{
	struct bio_vec *bvec = bio->bi_io_vec + bio->bi_vcnt - 1;
	struct extent_io_tree *tree;
	u64 start;
	u64 end;
	int whole_page;

	do {
		struct page *page = bvec->bv_page;
		tree = &BTRFS_I(page->mapping->host)->io_tree;

		start = ((u64)page->index << PAGE_CACHE_SHIFT) +
			 bvec->bv_offset;
		end = start + bvec->bv_len - 1;

		if (bvec->bv_offset == 0 && bvec->bv_len == PAGE_CACHE_SIZE)
			whole_page = 1;
		else
			whole_page = 0;

		if (--bvec >= bio->bi_io_vec)
			prefetchw(&bvec->bv_page->flags);

		if (end_extent_writepage(page, err, start, end))
			continue;

		if (whole_page)
			end_page_writeback(page);
		else
			check_page_writeback(tree, page);
	} while (bvec >= bio->bi_io_vec);

	bio_put(bio);
}