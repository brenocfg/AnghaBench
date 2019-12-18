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
struct strip_zone {unsigned int dev_start; } ;
struct request_queue {int /*<<< orphan*/  (* merge_bvec_fn ) (struct request_queue*,struct bvec_merge_data*,struct bio_vec*) ;struct mddev* queuedata; } ;
struct r0conf {int /*<<< orphan*/  has_merge_bvec; } ;
struct mddev {unsigned int chunk_sectors; struct r0conf* private; } ;
struct md_rdev {unsigned int data_offset; int /*<<< orphan*/  bdev; } ;
struct bvec_merge_data {unsigned int bi_sector; int bi_size; int /*<<< orphan*/  bi_bdev; } ;
struct bio_vec {int bv_len; } ;
typedef  unsigned int sector_t ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 struct strip_zone* find_zone (struct r0conf*,unsigned int*) ; 
 unsigned int get_start_sect (int /*<<< orphan*/ ) ; 
 scalar_t__ is_power_of_2 (unsigned int) ; 
 struct md_rdev* map_sector (struct mddev*,struct strip_zone*,unsigned int,unsigned int*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 unsigned int sector_div (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct bvec_merge_data*,struct bio_vec*) ; 

__attribute__((used)) static int raid0_mergeable_bvec(struct request_queue *q,
				struct bvec_merge_data *bvm,
				struct bio_vec *biovec)
{
	struct mddev *mddev = q->queuedata;
	struct r0conf *conf = mddev->private;
	sector_t sector = bvm->bi_sector + get_start_sect(bvm->bi_bdev);
	sector_t sector_offset = sector;
	int max;
	unsigned int chunk_sectors = mddev->chunk_sectors;
	unsigned int bio_sectors = bvm->bi_size >> 9;
	struct strip_zone *zone;
	struct md_rdev *rdev;
	struct request_queue *subq;

	if (is_power_of_2(chunk_sectors))
		max =  (chunk_sectors - ((sector & (chunk_sectors-1))
						+ bio_sectors)) << 9;
	else
		max =  (chunk_sectors - (sector_div(sector, chunk_sectors)
						+ bio_sectors)) << 9;
	if (max < 0)
		max = 0; /* bio_add cannot handle a negative return */
	if (max <= biovec->bv_len && bio_sectors == 0)
		return biovec->bv_len;
	if (max < biovec->bv_len)
		/* too small already, no need to check further */
		return max;
	if (!conf->has_merge_bvec)
		return max;

	/* May need to check subordinate device */
	sector = sector_offset;
	zone = find_zone(mddev->private, &sector_offset);
	rdev = map_sector(mddev, zone, sector, &sector_offset);
	subq = bdev_get_queue(rdev->bdev);
	if (subq->merge_bvec_fn) {
		bvm->bi_bdev = rdev->bdev;
		bvm->bi_sector = sector_offset + zone->dev_start +
			rdev->data_offset;
		return min(max, subq->merge_bvec_fn(subq, bvm, biovec));
	} else
		return max;
}