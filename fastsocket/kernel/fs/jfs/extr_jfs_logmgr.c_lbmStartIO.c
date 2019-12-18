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
struct lbuf {int l_blkno; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  l_page; struct jfs_log* l_log; } ;
struct jfs_log {int l2bsize; scalar_t__ no_integrity; int /*<<< orphan*/  bdev; } ;
struct bio {int bi_sector; int bi_vcnt; void* bi_size; struct lbuf* bi_private; int /*<<< orphan*/  (* bi_end_io ) (struct bio*,int /*<<< orphan*/ ) ;scalar_t__ bi_idx; TYPE_1__* bi_io_vec; int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  submitted; } ;
struct TYPE_3__ {int /*<<< orphan*/  bv_offset; void* bv_len; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 void* LOGPSIZE ; 
 int /*<<< orphan*/  WRITE_SYNC ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jfs_info (char*) ; 
 int /*<<< orphan*/  lbmIODone (struct bio*,int /*<<< orphan*/ ) ; 
 TYPE_2__ lmStat ; 
 int /*<<< orphan*/  submit_bio (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static void lbmStartIO(struct lbuf * bp)
{
	struct bio *bio;
	struct jfs_log *log = bp->l_log;

	jfs_info("lbmStartIO\n");

	bio = bio_alloc(GFP_NOFS, 1);
	bio->bi_sector = bp->l_blkno << (log->l2bsize - 9);
	bio->bi_bdev = log->bdev;
	bio->bi_io_vec[0].bv_page = bp->l_page;
	bio->bi_io_vec[0].bv_len = LOGPSIZE;
	bio->bi_io_vec[0].bv_offset = bp->l_offset;

	bio->bi_vcnt = 1;
	bio->bi_idx = 0;
	bio->bi_size = LOGPSIZE;

	bio->bi_end_io = lbmIODone;
	bio->bi_private = bp;

	/* check if journaling to disk has been disabled */
	if (log->no_integrity) {
		bio->bi_size = 0;
		lbmIODone(bio, 0);
	} else {
		submit_bio(WRITE_SYNC, bio);
		INCREMENT(lmStat.submitted);
	}
}