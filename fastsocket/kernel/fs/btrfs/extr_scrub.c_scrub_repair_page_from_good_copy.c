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
struct scrub_page {int physical; TYPE_1__* dev; int /*<<< orphan*/ * page; scalar_t__ io_error; } ;
struct scrub_block {scalar_t__ checksum_error; scalar_t__ header_error; struct scrub_page* pagev; } ;
struct bio {int bi_sector; int /*<<< orphan*/ * bi_private; int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  BTRFS_DEV_STAT_WRITE_ERRS ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_SIZE ; 
 int REQ_SYNC ; 
 int WRITE ; 
 int bio_add_page (struct bio*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  btrfs_dev_stat_inc_and_print (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfsic_submit_bio (int,struct bio*) ; 
 int /*<<< orphan*/  complete ; 
 int /*<<< orphan*/  scrub_complete_bio_end_io ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scrub_repair_page_from_good_copy(struct scrub_block *sblock_bad,
					    struct scrub_block *sblock_good,
					    int page_num, int force_write)
{
	struct scrub_page *page_bad = sblock_bad->pagev + page_num;
	struct scrub_page *page_good = sblock_good->pagev + page_num;

	BUG_ON(sblock_bad->pagev[page_num].page == NULL);
	BUG_ON(sblock_good->pagev[page_num].page == NULL);
	if (force_write || sblock_bad->header_error ||
	    sblock_bad->checksum_error || page_bad->io_error) {
		struct bio *bio;
		int ret;
		DECLARE_COMPLETION_ONSTACK(complete);

		bio = bio_alloc(GFP_NOFS, 1);
		if (!bio)
			return -EIO;
		bio->bi_bdev = page_bad->dev->bdev;
		bio->bi_sector = page_bad->physical >> 9;
		bio->bi_end_io = scrub_complete_bio_end_io;
		bio->bi_private = &complete;

		ret = bio_add_page(bio, page_good->page, PAGE_SIZE, 0);
		if (PAGE_SIZE != ret) {
			bio_put(bio);
			return -EIO;
		}
		btrfsic_submit_bio(WRITE | REQ_SYNC, bio);

		wait_for_completion(&complete);
		if (!bio_flagged(bio, BIO_UPTODATE)) {
			btrfs_dev_stat_inc_and_print(page_bad->dev,
				BTRFS_DEV_STAT_WRITE_ERRS);
			bio_put(bio);
			return -EIO;
		}
		bio_put(bio);
	}

	return 0;
}