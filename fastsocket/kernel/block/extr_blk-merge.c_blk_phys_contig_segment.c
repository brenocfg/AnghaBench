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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct bio {scalar_t__ bi_seg_back_size; scalar_t__ bi_seg_front_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOVEC_PHYS_MERGEABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_SEG_BOUNDARY (struct request_queue*,struct bio*,struct bio*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_CLUSTER ; 
 int /*<<< orphan*/  __BVEC_END (struct bio*) ; 
 int /*<<< orphan*/  __BVEC_START (struct bio*) ; 
 int /*<<< orphan*/  bio_has_data (struct bio*) ; 
 scalar_t__ queue_max_segment_size (struct request_queue*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int blk_phys_contig_segment(struct request_queue *q, struct bio *bio,
				   struct bio *nxt)
{
	if (!test_bit(QUEUE_FLAG_CLUSTER, &q->queue_flags))
		return 0;

	if (bio->bi_seg_back_size + nxt->bi_seg_front_size >
	    queue_max_segment_size(q))
		return 0;

	if (!bio_has_data(bio))
		return 1;

	if (!BIOVEC_PHYS_MERGEABLE(__BVEC_END(bio), __BVEC_START(nxt)))
		return 0;

	/*
	 * bio and nxt are contiguous in memory; check if the queue allows
	 * these two to be merged into one
	 */
	if (BIO_SEG_BOUNDARY(q, bio, nxt))
		return 1;

	return 0;
}