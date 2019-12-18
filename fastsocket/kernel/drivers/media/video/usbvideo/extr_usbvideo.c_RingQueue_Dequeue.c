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
struct RingQueue {int ri; int wi; int length; scalar_t__ queue; } ;

/* Variables and functions */
 int RingQueue_GetLength (struct RingQueue*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 

int RingQueue_Dequeue(struct RingQueue *rq, unsigned char *dst, int len)
{
	int rql, toread;

	assert(rq != NULL);
	assert(dst != NULL);

	rql = RingQueue_GetLength(rq);
	if(!rql)
		return 0;

	/* Clip requested length to available data */
	if(len > rql)
		len = rql;

	toread = len;
	if(rq->ri > rq->wi) {
		/* Read data from tail */
		int read = (toread < (rq->length - rq->ri)) ? toread : rq->length - rq->ri;
		memcpy(dst, rq->queue + rq->ri, read);
		toread -= read;
		dst += read;
		rq->ri = (rq->ri + read) & (rq->length-1);
	}
	if(toread) {
		/* Read data from head */
		memcpy(dst, rq->queue + rq->ri, toread);
		rq->ri = (rq->ri + toread) & (rq->length-1);
	}
	return len;
}