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
struct request_queue {int /*<<< orphan*/  (* merge_bvec_fn ) (struct request_queue*,struct bvec_merge_data*,struct bio_vec*) ;struct mddev* queuedata; } ;
struct mddev {int dummy; } ;
struct dev_info {unsigned long end_sector; TYPE_1__* rdev; } ;
struct bvec_merge_data {int bi_size; unsigned long bi_sector; int /*<<< orphan*/  bi_bdev; } ;
struct bio_vec {int bv_len; } ;
typedef  unsigned long sector_t ;
struct TYPE_2__ {unsigned long sectors; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 unsigned long get_start_sect (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct bvec_merge_data*,struct bio_vec*) ; 
 struct dev_info* which_dev (struct mddev*,unsigned long) ; 

__attribute__((used)) static int linear_mergeable_bvec(struct request_queue *q,
				 struct bvec_merge_data *bvm,
				 struct bio_vec *biovec)
{
	struct mddev *mddev = q->queuedata;
	struct dev_info *dev0;
	unsigned long maxsectors, bio_sectors = bvm->bi_size >> 9;
	sector_t sector = bvm->bi_sector + get_start_sect(bvm->bi_bdev);
	int maxbytes = biovec->bv_len;
	struct request_queue *subq;

	rcu_read_lock();
	dev0 = which_dev(mddev, sector);
	maxsectors = dev0->end_sector - sector;
	subq = bdev_get_queue(dev0->rdev->bdev);
	if (subq->merge_bvec_fn) {
		bvm->bi_bdev = dev0->rdev->bdev;
		bvm->bi_sector -= dev0->end_sector - dev0->rdev->sectors;
		maxbytes = min(maxbytes, subq->merge_bvec_fn(subq, bvm,
							     biovec));
	}
	rcu_read_unlock();

	if (maxsectors < bio_sectors)
		maxsectors = 0;
	else
		maxsectors -= bio_sectors;

	if (maxsectors <= (PAGE_SIZE >> 9 ) && bio_sectors == 0)
		return maxbytes;

	if (maxsectors > (maxbytes >> 9))
		return maxbytes;
	else
		return maxsectors << 9;
}