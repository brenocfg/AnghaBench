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
struct request_queue {int /*<<< orphan*/ * rq_timed_out_fn; } ;
typedef  int /*<<< orphan*/  rq_timed_out_fn ;

/* Variables and functions */

void blk_queue_rq_timed_out(struct request_queue *q, rq_timed_out_fn *fn)
{
	q->rq_timed_out_fn = fn;
}