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
struct buffer_head {int b_blocknr; int b_size; int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_end_io; } ;
struct bio {int bi_sector; int bi_vcnt; int bi_size; struct buffer_head* bi_private; int /*<<< orphan*/  bi_end_io; scalar_t__ bi_idx; TYPE_1__* bi_io_vec; int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_2__ {int bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_EOPNOTSUPP ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int WRITE ; 
 int WRITE_BARRIER ; 
 int /*<<< orphan*/  bh_offset (struct buffer_head*) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_ordered (struct buffer_head*) ; 
 int buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  end_bio_bh_io_sync ; 
 int /*<<< orphan*/  guard_bh_eod (int,struct bio*,struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bio (int,struct bio*) ; 
 scalar_t__ test_set_buffer_req (struct buffer_head*) ; 

int submit_bh(int rw, struct buffer_head * bh)
{
	struct bio *bio;
	int ret = 0;

	BUG_ON(!buffer_locked(bh));
	BUG_ON(!buffer_mapped(bh));
	BUG_ON(!bh->b_end_io);
	BUG_ON(buffer_delay(bh));
	BUG_ON(buffer_unwritten(bh));

	/*
	 * Mask in barrier bit for a write (could be either a WRITE or a
	 * WRITE_SYNC
	 */
	if (buffer_ordered(bh) && (rw & WRITE))
		rw |= WRITE_BARRIER;

	/*
	 * Only clear out a write error when rewriting
	 */
	if (test_set_buffer_req(bh) && (rw & WRITE))
		clear_buffer_write_io_error(bh);

	/*
	 * from here on down, it's all bio -- do the initial mapping,
	 * submit_bio -> generic_make_request may further map this bio around
	 */
	bio = bio_alloc(GFP_NOIO, 1);

	bio->bi_sector = bh->b_blocknr * (bh->b_size >> 9);
	bio->bi_bdev = bh->b_bdev;
	bio->bi_io_vec[0].bv_page = bh->b_page;
	bio->bi_io_vec[0].bv_len = bh->b_size;
	bio->bi_io_vec[0].bv_offset = bh_offset(bh);

	bio->bi_vcnt = 1;
	bio->bi_idx = 0;
	bio->bi_size = bh->b_size;

	bio->bi_end_io = end_bio_bh_io_sync;
	bio->bi_private = bh;

	/* Take care of bh's that straddle the end of the device */
	guard_bh_eod(rw, bio, bh);

	bio_get(bio);
	submit_bio(rw, bio);

	if (bio_flagged(bio, BIO_EOPNOTSUPP))
		ret = -EOPNOTSUPP;

	bio_put(bio);
	return ret;
}