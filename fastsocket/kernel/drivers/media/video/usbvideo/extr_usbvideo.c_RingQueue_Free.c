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
struct RingQueue {scalar_t__ length; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */
 scalar_t__ RingQueue_IsAllocated (struct RingQueue*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbvideo_rvfree (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void RingQueue_Free(struct RingQueue *rq)
{
	assert(rq != NULL);
	if (RingQueue_IsAllocated(rq)) {
		usbvideo_rvfree(rq->queue, rq->length);
		rq->queue = NULL;
		rq->length = 0;
	}
}