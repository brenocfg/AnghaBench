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
typedef  int /*<<< orphan*/  unprep_rq_fn ;
struct request_queue {int /*<<< orphan*/ * unprep_rq_fn; } ;

/* Variables and functions */

void blk_queue_unprep_rq(struct request_queue *q, unprep_rq_fn *ufn)
{
	q->unprep_rq_fn = ufn;
}