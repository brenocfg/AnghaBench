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
struct multipath_info {TYPE_1__* rdev; } ;
struct bio {int bi_rw; struct multipath_bh* bi_private; int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; } ;
struct multipath_bh {scalar_t__ path; struct bio bio; struct mddev* mddev; struct bio* master_bio; } ;
struct mpconf {struct multipath_info* multipaths; int /*<<< orphan*/  pool; } ;
struct mddev {struct mpconf* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; scalar_t__ data_offset; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int BIO_RW_FAILFAST_TRANSPORT ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  md_flush_request (struct mddev*,struct bio*) ; 
 struct multipath_bh* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct multipath_bh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multipath_end_request ; 
 scalar_t__ multipath_map (struct mpconf*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int multipath_make_request(struct mddev *mddev, struct bio * bio)
{
	struct mpconf *conf = mddev->private;
	struct multipath_bh * mp_bh;
	struct multipath_info *multipath;

	if (unlikely(bio->bi_rw & BIO_FLUSH)) {
		md_flush_request(mddev, bio);
		return 0;
	}

	mp_bh = mempool_alloc(conf->pool, GFP_NOIO);

	mp_bh->master_bio = bio;
	mp_bh->mddev = mddev;

	mp_bh->path = multipath_map(conf);
	if (mp_bh->path < 0) {
		bio_endio(bio, -EIO);
		mempool_free(mp_bh, conf->pool);
		return 0;
	}
	multipath = conf->multipaths + mp_bh->path;

	mp_bh->bio = *bio;
	mp_bh->bio.bi_sector += multipath->rdev->data_offset;
	mp_bh->bio.bi_bdev = multipath->rdev->bdev;
	mp_bh->bio.bi_rw |= (1 << BIO_RW_FAILFAST_TRANSPORT);
	mp_bh->bio.bi_end_io = multipath_end_request;
	mp_bh->bio.bi_private = mp_bh;
	generic_make_request(&mp_bh->bio);
	return 0;
}