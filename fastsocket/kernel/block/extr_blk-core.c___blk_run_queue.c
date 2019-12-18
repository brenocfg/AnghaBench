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
struct request_queue {int /*<<< orphan*/  (* request_fn ) (struct request_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_stopped (struct request_queue*) ; 
 int /*<<< orphan*/  blk_remove_plug (struct request_queue*) ; 
 scalar_t__ elv_queue_empty (struct request_queue*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __blk_run_queue(struct request_queue *q)
{
	blk_remove_plug(q);

	if (unlikely(blk_queue_stopped(q)))
		return;

	if (elv_queue_empty(q))
		return;

	q->request_fn(q);
}