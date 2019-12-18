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
struct RingQueue {int length; int /*<<< orphan*/ * queue; scalar_t__ wi; scalar_t__ ri; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * usbvideo_rvmalloc (int) ; 

__attribute__((used)) static void RingQueue_Allocate(struct RingQueue *rq, int rqLen)
{
	/* Make sure the requested size is a power of 2 and
	   round up if necessary. This allows index wrapping
	   using masks rather than modulo */

	int i = 1;
	assert(rq != NULL);
	assert(rqLen > 0);

	while(rqLen >> i)
		i++;
	if(rqLen != 1 << (i-1))
		rqLen = 1 << i;

	rq->length = rqLen;
	rq->ri = rq->wi = 0;
	rq->queue = usbvideo_rvmalloc(rq->length);
	assert(rq->queue != NULL);
}