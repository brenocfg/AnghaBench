#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fib {int /*<<< orphan*/  hw_fib_va; struct aac_dev* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * producer; } ;
struct aac_queue {int /*<<< orphan*/  lock; TYPE_2__ headers; int /*<<< orphan*/  numpending; } ;
struct aac_dev {TYPE_1__* queues; } ;
struct TYPE_6__ {unsigned long irq_mod; } ;
struct TYPE_4__ {struct aac_queue* queue; } ;

/* Variables and functions */
 size_t AdapNormCmdQueue ; 
 int /*<<< orphan*/  aac_adapter_notify (struct aac_dev*,size_t) ; 
 TYPE_3__ aac_config ; 
 int /*<<< orphan*/  aac_queue_get (struct aac_dev*,scalar_t__*,size_t,int /*<<< orphan*/ ,int,struct fib*,unsigned long*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int aac_rx_deliver_producer(struct fib * fib)
{
	struct aac_dev *dev = fib->dev;
	struct aac_queue *q = &dev->queues->queue[AdapNormCmdQueue];
	unsigned long qflags;
	u32 Index;
	unsigned long nointr = 0;

	spin_lock_irqsave(q->lock, qflags);
	aac_queue_get( dev, &Index, AdapNormCmdQueue, fib->hw_fib_va, 1, fib, &nointr);

	q->numpending++;
	*(q->headers.producer) = cpu_to_le32(Index + 1);
	spin_unlock_irqrestore(q->lock, qflags);
	if (!(nointr & aac_config.irq_mod))
		aac_adapter_notify(dev, AdapNormCmdQueue);

	return 0;
}