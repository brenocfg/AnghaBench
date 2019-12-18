#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int actual; int length; int /*<<< orphan*/ * buf; } ;
struct lh7a40x_request {TYPE_1__ req; } ;
struct lh7a40x_ep {scalar_t__ fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int,int,int /*<<< orphan*/  volatile*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ int write_packet(struct lh7a40x_ep *ep,
				   struct lh7a40x_request *req, int max)
{
	u8 *buf;
	int length, count;
	volatile u32 *fifo = (volatile u32 *)ep->fifo;

	buf = req->req.buf + req->req.actual;
	prefetch(buf);

	length = req->req.length - req->req.actual;
	length = min(length, max);
	req->req.actual += length;

	DEBUG("Write %d (max %d), fifo %p\n", length, max, fifo);

	count = length;
	while (count--) {
		*fifo = *buf++;
	}

	return length;
}