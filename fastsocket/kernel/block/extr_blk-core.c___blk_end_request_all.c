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
struct request {struct request* next_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __blk_end_bidi_request (struct request*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  blk_bidi_rq (struct request*) ; 
 unsigned int blk_rq_bytes (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __blk_end_request_all(struct request *rq, int error)
{
	bool pending;
	unsigned int bidi_bytes = 0;

	if (unlikely(blk_bidi_rq(rq)))
		bidi_bytes = blk_rq_bytes(rq->next_rq);

	pending = __blk_end_bidi_request(rq, error, blk_rq_bytes(rq), bidi_bytes);
	BUG_ON(pending);
}