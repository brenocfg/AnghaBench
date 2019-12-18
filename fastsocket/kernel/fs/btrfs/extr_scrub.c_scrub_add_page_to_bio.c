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
struct scrub_page {int physical; scalar_t__ logical; int /*<<< orphan*/  page; struct scrub_block* sblock; } ;
struct scrub_dev {int curr; int first_free; scalar_t__ pages_per_bio; TYPE_1__* dev; struct scrub_bio** bios; int /*<<< orphan*/  list_wait; int /*<<< orphan*/  list_lock; } ;
struct scrub_block {int /*<<< orphan*/  outstanding_pages; } ;
struct scrub_bio {int next_free; int page_count; int physical; scalar_t__ logical; struct bio* bio; struct scrub_page** pagev; scalar_t__ err; } ;
struct bio {int bi_sector; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_end_io; struct scrub_bio* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bio_add_page (struct bio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  scrub_bio_end_io ; 
 int /*<<< orphan*/  scrub_block_get (struct scrub_block*) ; 
 int /*<<< orphan*/  scrub_submit (struct scrub_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int scrub_add_page_to_bio(struct scrub_dev *sdev,
				 struct scrub_page *spage)
{
	struct scrub_block *sblock = spage->sblock;
	struct scrub_bio *sbio;
	int ret;

again:
	/*
	 * grab a fresh bio or wait for one to become available
	 */
	while (sdev->curr == -1) {
		spin_lock(&sdev->list_lock);
		sdev->curr = sdev->first_free;
		if (sdev->curr != -1) {
			sdev->first_free = sdev->bios[sdev->curr]->next_free;
			sdev->bios[sdev->curr]->next_free = -1;
			sdev->bios[sdev->curr]->page_count = 0;
			spin_unlock(&sdev->list_lock);
		} else {
			spin_unlock(&sdev->list_lock);
			wait_event(sdev->list_wait, sdev->first_free != -1);
		}
	}
	sbio = sdev->bios[sdev->curr];
	if (sbio->page_count == 0) {
		struct bio *bio;

		sbio->physical = spage->physical;
		sbio->logical = spage->logical;
		bio = sbio->bio;
		if (!bio) {
			bio = bio_alloc(GFP_NOFS, sdev->pages_per_bio);
			if (!bio)
				return -ENOMEM;
			sbio->bio = bio;
		}

		bio->bi_private = sbio;
		bio->bi_end_io = scrub_bio_end_io;
		bio->bi_bdev = sdev->dev->bdev;
		bio->bi_sector = spage->physical >> 9;
		sbio->err = 0;
	} else if (sbio->physical + sbio->page_count * PAGE_SIZE !=
		   spage->physical ||
		   sbio->logical + sbio->page_count * PAGE_SIZE !=
		   spage->logical) {
		scrub_submit(sdev);
		goto again;
	}

	sbio->pagev[sbio->page_count] = spage;
	ret = bio_add_page(sbio->bio, spage->page, PAGE_SIZE, 0);
	if (ret != PAGE_SIZE) {
		if (sbio->page_count < 1) {
			bio_put(sbio->bio);
			sbio->bio = NULL;
			return -EIO;
		}
		scrub_submit(sdev);
		goto again;
	}

	scrub_block_get(sblock); /* one for the added page */
	atomic_inc(&sblock->outstanding_pages);
	sbio->page_count++;
	if (sbio->page_count == sdev->pages_per_bio)
		scrub_submit(sdev);

	return 0;
}