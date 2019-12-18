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
struct request_queue {struct mddev* queuedata; } ;
struct mddev {unsigned int chunk_sectors; unsigned int new_chunk_sectors; } ;
struct bvec_merge_data {unsigned int bi_sector; int bi_size; int bi_rw; int /*<<< orphan*/  bi_bdev; } ;
struct bio_vec {int bv_len; } ;
typedef  unsigned int sector_t ;

/* Variables and functions */
 int WRITE ; 
 unsigned int get_start_sect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raid5_mergeable_bvec(struct request_queue *q,
				struct bvec_merge_data *bvm,
				struct bio_vec *biovec)
{
	struct mddev *mddev = q->queuedata;
	sector_t sector = bvm->bi_sector + get_start_sect(bvm->bi_bdev);
	int max;
	unsigned int chunk_sectors = mddev->chunk_sectors;
	unsigned int bio_sectors = bvm->bi_size >> 9;

	if ((bvm->bi_rw & 1) == WRITE)
		return biovec->bv_len; /* always allow writes to be mergeable */

	if (mddev->new_chunk_sectors < mddev->chunk_sectors)
		chunk_sectors = mddev->new_chunk_sectors;
	max =  (chunk_sectors - ((sector & (chunk_sectors - 1)) + bio_sectors)) << 9;
	if (max < 0) max = 0;
	if (max <= biovec->bv_len && bio_sectors == 0)
		return biovec->bv_len;
	else
		return max;
}