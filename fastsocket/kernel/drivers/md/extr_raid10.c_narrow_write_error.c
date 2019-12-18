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
struct r10conf {TYPE_1__* mirrors; } ;
struct r10bio {int sectors; int sector; TYPE_3__* devs; struct mddev* mddev; struct bio* master_bio; } ;
struct mddev {struct r10conf* private; } ;
struct TYPE_5__ {int shift; } ;
struct md_rdev {int /*<<< orphan*/  bdev; TYPE_2__ badblocks; } ;
struct bio {int bi_sector; int /*<<< orphan*/  bi_bdev; } ;
typedef  int sector_t ;
struct TYPE_6__ {size_t devnum; int addr; } ;
struct TYPE_4__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  WRITE ; 
 struct bio* bio_clone_mddev (struct bio*,int /*<<< orphan*/ ,struct mddev*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int choose_data_offset (struct r10bio*,struct md_rdev*) ; 
 int /*<<< orphan*/  md_trim_bio (struct bio*,int,int) ; 
 scalar_t__ rdev_set_badblocks (struct md_rdev*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ submit_bio_wait (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static int narrow_write_error(struct r10bio *r10_bio, int i)
{
	struct bio *bio = r10_bio->master_bio;
	struct mddev *mddev = r10_bio->mddev;
	struct r10conf *conf = mddev->private;
	struct md_rdev *rdev = conf->mirrors[r10_bio->devs[i].devnum].rdev;
	/* bio has the data to be written to slot 'i' where
	 * we just recently had a write error.
	 * We repeatedly clone the bio and trim down to one block,
	 * then try the write.  Where the write fails we record
	 * a bad block.
	 * It is conceivable that the bio doesn't exactly align with
	 * blocks.  We must handle this.
	 *
	 * We currently own a reference to the rdev.
	 */

	int block_sectors;
	sector_t sector;
	int sectors;
	int sect_to_write = r10_bio->sectors;
	int ok = 1;

	if (rdev->badblocks.shift < 0)
		return 0;

	block_sectors = 1 << rdev->badblocks.shift;
	sector = r10_bio->sector;
	sectors = ((r10_bio->sector + block_sectors)
		   & ~(sector_t)(block_sectors - 1))
		- sector;

	while (sect_to_write) {
		struct bio *wbio;
		if (sectors > sect_to_write)
			sectors = sect_to_write;
		/* Write at 'sector' for 'sectors' */
		wbio = bio_clone_mddev(bio, GFP_NOIO, mddev);
		md_trim_bio(wbio, sector - bio->bi_sector, sectors);
		wbio->bi_sector = (r10_bio->devs[i].addr+
				   choose_data_offset(r10_bio, rdev) +
				   (sector - r10_bio->sector));
		wbio->bi_bdev = rdev->bdev;
		if (submit_bio_wait(WRITE, wbio) == 0)
			/* Failure! */
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