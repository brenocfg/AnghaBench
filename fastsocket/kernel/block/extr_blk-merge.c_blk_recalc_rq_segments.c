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
struct request {int /*<<< orphan*/  bio; int /*<<< orphan*/  q; int /*<<< orphan*/  nr_phys_segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_recalc_rq_segments (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void blk_recalc_rq_segments(struct request *rq)
{
	rq->nr_phys_segments = __blk_recalc_rq_segments(rq->q, rq->bio);
}