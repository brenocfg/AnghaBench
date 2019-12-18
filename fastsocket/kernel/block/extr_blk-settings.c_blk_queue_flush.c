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
struct request_queue {unsigned int flush_flags; } ;

/* Variables and functions */
 unsigned int REQ_FLUSH ; 
 unsigned int REQ_FUA ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

void blk_queue_flush(struct request_queue *q, unsigned int flush)
{
	WARN_ON_ONCE(flush & ~(REQ_FLUSH | REQ_FUA));

	if (WARN_ON_ONCE(!(flush & REQ_FLUSH) && (flush & REQ_FUA)))
		flush &= ~REQ_FUA;

	q->flush_flags = flush & (REQ_FLUSH | REQ_FUA);
}