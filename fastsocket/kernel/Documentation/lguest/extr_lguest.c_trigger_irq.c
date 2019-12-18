#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long irq; } ;
struct TYPE_7__ {TYPE_4__* avail; } ;
struct virtqueue {TYPE_2__ config; TYPE_3__ vring; TYPE_1__* dev; scalar_t__ pending_used; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int flags; scalar_t__ idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq_on_empty; } ;

/* Variables and functions */
 unsigned long LHREQ_IRQ ; 
 int VRING_AVAIL_F_NO_INTERRUPT ; 
 int /*<<< orphan*/  err (int,char*,unsigned long) ; 
 scalar_t__ lg_last_avail (struct virtqueue*) ; 
 int /*<<< orphan*/  lguest_fd ; 
 scalar_t__ write (int /*<<< orphan*/ ,unsigned long*,int) ; 

__attribute__((used)) static void trigger_irq(struct virtqueue *vq)
{
	unsigned long buf[] = { LHREQ_IRQ, vq->config.irq };

	/* Don't inform them if nothing used. */
	if (!vq->pending_used)
		return;
	vq->pending_used = 0;

	/* If they don't want an interrupt, don't send one... */
	if (vq->vring.avail->flags & VRING_AVAIL_F_NO_INTERRUPT) {
		/* ... unless they've asked us to force one on empty. */
		if (!vq->dev->irq_on_empty
		    || lg_last_avail(vq) != vq->vring.avail->idx)
			return;
	}

	/* Send the Guest an interrupt tell them we used something up. */
	if (write(lguest_fd, buf, sizeof(buf)) != 0)
		err(1, "Triggering irq %i", vq->config.irq);
}