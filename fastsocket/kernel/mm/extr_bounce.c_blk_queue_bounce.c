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
struct request_queue {int bounce_gfp; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  __blk_queue_bounce (struct request_queue*,struct bio**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_has_data (struct bio*) ; 
 scalar_t__ blk_max_pfn ; 
 int /*<<< orphan*/ * isa_page_pool ; 
 int must_snapshot_stable_pages (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/ * page_pool ; 
 scalar_t__ queue_bounce_pfn (struct request_queue*) ; 

void blk_queue_bounce(struct request_queue *q, struct bio **bio_orig)
{
	int must_bounce;
	mempool_t *pool;

	/*
	 * Data-less bio, nothing to bounce
	 */
	if (!bio_has_data(*bio_orig))
		return;

	must_bounce = must_snapshot_stable_pages(q, *bio_orig);

	/*
	 * for non-isa bounce case, just check if the bounce pfn is equal
	 * to or bigger than the highest pfn in the system -- in that case,
	 * don't waste time iterating over bio segments
	 */
	if (!(q->bounce_gfp & GFP_DMA)) {
		if (queue_bounce_pfn(q) >= blk_max_pfn && !must_bounce)
			return;
		pool = page_pool;
	} else {
		BUG_ON(!isa_page_pool);
		pool = isa_page_pool;
	}

	/*
	 * slow path
	 */
	__blk_queue_bounce(q, bio_orig, pool, must_bounce);
}