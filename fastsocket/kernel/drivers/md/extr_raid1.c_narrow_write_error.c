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
struct r1conf {TYPE_1__* mirrors; } ;
struct r1bio {int sectors; int sector; int behind_page_count; TYPE_3__* master_bio; struct bio_vec* behind_bvecs; int /*<<< orphan*/  state; struct mddev* mddev; } ;
struct mddev {struct r1conf* private; } ;
struct TYPE_5__ {int shift; } ;
struct md_rdev {int /*<<< orphan*/  bdev; scalar_t__ data_offset; TYPE_2__ badblocks; } ;
struct bio_vec {int /*<<< orphan*/ * bv_page; } ;
struct bio {int bi_sector; int bi_vcnt; int bi_size; int bi_idx; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_rw; int /*<<< orphan*/  bi_io_vec; } ;
typedef  int sector_t ;
struct TYPE_6__ {int bi_vcnt; int bi_idx; struct bio_vec* bi_io_vec; } ;
struct TYPE_4__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  R1BIO_BehindIO ; 
 int /*<<< orphan*/  WRITE ; 
 struct bio* bio_alloc_mddev (int /*<<< orphan*/ ,int,struct mddev*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  md_trim_bio (struct bio*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct bio_vec*,int) ; 
 scalar_t__ rdev_set_badblocks (struct md_rdev*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ submit_bio_wait (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int narrow_write_error(struct r1bio *r1_bio, int i)
{
	struct mddev *mddev = r1_bio->mddev;
	struct r1conf *conf = mddev->private;
	struct md_rdev *rdev = conf->mirrors[i].rdev;
	int vcnt, idx;
	struct bio_vec *vec;

	/* bio has the data to be written to device 'i' where
	 * we just recently had a write error.
	 * We repeatedly clone the bio and trim down to one block,
	 * then try the write.  Where the write fails we record
	 * a bad block.
	 * It is conceivable that the bio doesn't exactly align with
	 * blocks.  We must handle this somehow.
	 *
	 * We currently own a reference on the rdev.
	 */

	int block_sectors;
	sector_t sector;
	int sectors;
	int sect_to_write = r1_bio->sectors;
	int ok = 1;

	if (rdev->badblocks.shift < 0)
		return 0;

	block_sectors = 1 << rdev->badblocks.shift;
	sector = r1_bio->sector;
	sectors = ((sector + block_sectors)
		   & ~(sector_t)(block_sectors - 1))
		- sector;

	if (test_bit(R1BIO_BehindIO, &r1_bio->state)) {
		vcnt = r1_bio->behind_page_count;
		vec = r1_bio->behind_bvecs;
		idx = 0;
		while (vec[idx].bv_page == NULL)
			idx++;
	} else {
		vcnt = r1_bio->master_bio->bi_vcnt;
		vec = r1_bio->master_bio->bi_io_vec;
		idx = r1_bio->master_bio->bi_idx;
	}
	while (sect_to_write) {
		struct bio *wbio;
		if (sectors > sect_to_write)
			sectors = sect_to_write;
		/* Write at 'sector' for 'sectors'*/

		wbio = bio_alloc_mddev(GFP_NOIO, vcnt, mddev);
		memcpy(wbio->bi_io_vec, vec, vcnt * sizeof(struct bio_vec));
		wbio->bi_sector = r1_bio->sector;
		wbio->bi_rw = WRITE;
		wbio->bi_vcnt = vcnt;
		wbio->bi_size = r1_bio->sectors << 9;
		wbio->bi_idx = idx;

		md_trim_bio(wbio, sector - r1_bio->sector, sectors);
		wbio->bi_sector += rdev->data_offset;
		wbio->bi_bdev = rdev->bdev;
		if (submit_bio_wait(WRITE, wbio) == 0)
			/* failure! */
			ok = rdev_set_badblocks(rdev, sector,
						sectors, 0)
				&& ok;

		bio_put(wbio);
		sect_to_write -= sectors;
		sector += sectors;
		sectors = block_sectors;
	}
	return ok;
}