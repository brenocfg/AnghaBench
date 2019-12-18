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
struct r1conf {int raid_disks; TYPE_1__* mirrors; } ;
struct r1bio {int read_disk; int sectors; scalar_t__ sector; struct bio** bios; struct mddev* mddev; } ;
struct page {int dummy; } ;
struct mddev {int recovery; int /*<<< orphan*/  resync_mismatches; struct r1conf* private; } ;
struct bio_vec {int bv_len; struct page* bv_page; scalar_t__ bv_offset; } ;
struct bio {int bi_flags; int bi_vcnt; int bi_size; struct bio_vec* bi_io_vec; int /*<<< orphan*/  bi_bdev; scalar_t__ bi_sector; int /*<<< orphan*/ * bi_next; scalar_t__ bi_phys_segments; scalar_t__ bi_idx; int /*<<< orphan*/ * bi_end_io; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; scalar_t__ data_offset; } ;
struct TYPE_3__ {TYPE_2__* rdev; } ;

/* Variables and functions */
 int BIO_POOL_MASK ; 
 int BIO_UPTODATE ; 
 int MD_RECOVERY_CHECK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * end_sync_read ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  rdev_dec_pending (TYPE_2__*,struct mddev*) ; 
 scalar_t__ test_bit (int,int*) ; 

__attribute__((used)) static int process_checks(struct r1bio *r1_bio)
{
	/* We have read all readable devices.  If we haven't
	 * got the block, then there is no hope left.
	 * If we have, then we want to do a comparison
	 * and skip the write if everything is the same.
	 * If any blocks failed to read, then we need to
	 * attempt an over-write
	 */
	struct mddev *mddev = r1_bio->mddev;
	struct r1conf *conf = mddev->private;
	int primary;
	int i;
	int vcnt;

	for (primary = 0; primary < conf->raid_disks * 2; primary++)
		if (r1_bio->bios[primary]->bi_end_io == end_sync_read &&
		    test_bit(BIO_UPTODATE, &r1_bio->bios[primary]->bi_flags)) {
			r1_bio->bios[primary]->bi_end_io = NULL;
			rdev_dec_pending(conf->mirrors[primary].rdev, mddev);
			break;
		}
	r1_bio->read_disk = primary;
	vcnt = (r1_bio->sectors + PAGE_SIZE / 512 - 1) >> (PAGE_SHIFT - 9);
	for (i = 0; i < conf->raid_disks * 2; i++) {
		int j;
		struct bio *pbio = r1_bio->bios[primary];
		struct bio *sbio = r1_bio->bios[i];
		int size;

		if (r1_bio->bios[i]->bi_end_io != end_sync_read)
			continue;

		if (test_bit(BIO_UPTODATE, &sbio->bi_flags)) {
			for (j = vcnt; j-- ; ) {
				struct page *p, *s;
				p = pbio->bi_io_vec[j].bv_page;
				s = sbio->bi_io_vec[j].bv_page;
				if (memcmp(page_address(p),
					   page_address(s),
					   sbio->bi_io_vec[j].bv_len))
					break;
			}
		} else
			j = 0;
		if (j >= 0)
			atomic64_add(r1_bio->sectors, &mddev->resync_mismatches);
		if (j < 0 || (test_bit(MD_RECOVERY_CHECK, &mddev->recovery)
			      && test_bit(BIO_UPTODATE, &sbio->bi_flags))) {
			/* No need to write to this device. */
			sbio->bi_end_io = NULL;
			rdev_dec_pending(conf->mirrors[i].rdev, mddev);
			continue;
		}
		/* fixup the bio for reuse */
		sbio->bi_vcnt = vcnt;
		sbio->bi_size = r1_bio->sectors << 9;
		sbio->bi_idx = 0;
		sbio->bi_phys_segments = 0;
		sbio->bi_flags &= ~(BIO_POOL_MASK - 1);
		sbio->bi_flags |= 1 << BIO_UPTODATE;
		sbio->bi_next = NULL;
		sbio->bi_sector = r1_bio->sector +
			conf->mirrors[i].rdev->data_offset;
		sbio->bi_bdev = conf->mirrors[i].rdev->bdev;
		size = sbio->bi_size;
		for (j = 0; j < vcnt ; j++) {
			struct bio_vec *bi;
			bi = &sbio->bi_io_vec[j];
			bi->bv_offset = 0;
			if (size > PAGE_SIZE)
				bi->bv_len = PAGE_SIZE;
			else
				bi->bv_len = size;
			size -= PAGE_SIZE;
			memcpy(page_address(bi->bv_page),
			       page_address(pbio->bi_io_vec[j].bv_page),
			       PAGE_SIZE);
		}
	}
	return 0;
}