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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int READ ; 
 int WRITE ; 
 int __GFP_WAIT ; 
 struct request* get_request (struct request_queue*,int,int /*<<< orphan*/ *,int) ; 
 struct request* get_request_wait (struct request_queue*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

struct request *blk_get_request(struct request_queue *q, int rw, gfp_t gfp_mask)
{
	struct request *rq;

	BUG_ON(rw != READ && rw != WRITE);

	spin_lock_irq(q->queue_lock);
	if (gfp_mask & __GFP_WAIT)
		rq = get_request_wait(q, rw, NULL);
	else
		rq = get_request(q, rw, NULL, gfp_mask);
	if (!rq)
		spin_unlock_irq(q->queue_lock);
	/* q->queue_lock is unlocked at this point */

	return rq;
}