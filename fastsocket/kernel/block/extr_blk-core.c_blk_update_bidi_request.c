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
struct request {int /*<<< orphan*/  rq_disk; int /*<<< orphan*/  q; struct request* next_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_disk_randomness (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_bidi_rq (struct request*) ; 
 scalar_t__ blk_queue_add_random (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_update_request (struct request*,int,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool blk_update_bidi_request(struct request *rq, int error,
				    unsigned int nr_bytes,
				    unsigned int bidi_bytes)
{
	if (blk_update_request(rq, error, nr_bytes))
		return true;

	/* Bidi request must be completed as a whole */
	if (unlikely(blk_bidi_rq(rq)) &&
	    blk_update_request(rq->next_rq, error, bidi_bytes))
		return true;

	if (blk_queue_add_random(rq->q))
		add_disk_randomness(rq->rq_disk);

	return false;
}