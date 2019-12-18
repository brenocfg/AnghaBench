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
struct page {int dummy; } ;
struct bio_vec {struct page* bv_page; } ;
struct bio {int bi_vcnt; struct bio* bi_private; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 scalar_t__ PageCompound (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 struct bio* bio_dirty_list ; 
 int /*<<< orphan*/  bio_dirty_lock ; 
 int /*<<< orphan*/  bio_dirty_work ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void bio_check_pages_dirty(struct bio *bio)
{
	struct bio_vec *bvec = bio->bi_io_vec;
	int nr_clean_pages = 0;
	int i;

	for (i = 0; i < bio->bi_vcnt; i++) {
		struct page *page = bvec[i].bv_page;

		if (PageDirty(page) || PageCompound(page)) {
			page_cache_release(page);
			bvec[i].bv_page = NULL;
		} else {
			nr_clean_pages++;
		}
	}

	if (nr_clean_pages) {
		unsigned long flags;

		spin_lock_irqsave(&bio_dirty_lock, flags);
		bio->bi_private = bio_dirty_list;
		bio_dirty_list = bio;
		spin_unlock_irqrestore(&bio_dirty_lock, flags);
		schedule_work(&bio_dirty_work);
	} else {
		bio_put(bio);
	}
}