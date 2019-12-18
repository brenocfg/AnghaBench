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
struct RingQueue {scalar_t__ length; int wi; int queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_QUEUE_ADVANCE_INDEX (struct RingQueue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int,unsigned char const*,int) ; 
 int /*<<< orphan*/  wi ; 

int RingQueue_Enqueue(struct RingQueue *rq, const unsigned char *cdata, int n)
{
	int enqueued = 0;

	assert(rq != NULL);
	assert(cdata != NULL);
	assert(rq->length > 0);
	while (n > 0) {
		int m, q_avail;

		/* Calculate the largest chunk that fits the tail of the ring */
		q_avail = rq->length - rq->wi;
		if (q_avail <= 0) {
			rq->wi = 0;
			q_avail = rq->length;
		}
		m = n;
		assert(q_avail > 0);
		if (m > q_avail)
			m = q_avail;

		memcpy(rq->queue + rq->wi, cdata, m);
		RING_QUEUE_ADVANCE_INDEX(rq, wi, m);
		cdata += m;
		enqueued += m;
		n -= m;
	}
	return enqueued;
}