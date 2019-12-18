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
struct request_queue {int /*<<< orphan*/ * merge_bvec_fn; } ;
typedef  int /*<<< orphan*/  merge_bvec_fn ;

/* Variables and functions */

void blk_queue_merge_bvec(struct request_queue *q, merge_bvec_fn *mbfn)
{
	q->merge_bvec_fn = mbfn;
}