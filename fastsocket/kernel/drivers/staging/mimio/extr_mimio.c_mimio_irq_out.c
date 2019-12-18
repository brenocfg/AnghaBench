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
struct urb {int /*<<< orphan*/  status; struct mimio* context; } ;
struct mimio {int /*<<< orphan*/  waitq; int /*<<< orphan*/  txlock; int /*<<< orphan*/  txflags; TYPE_1__* idev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIMIO_TXDONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mimio_irq_out(struct urb *urb)
{
	unsigned long flags;
	struct mimio *mimio;

	mimio = urb->context;

	if (urb->status)
		dev_dbg(&mimio->idev->dev, "urb-status: %d.\n", urb->status);

	spin_lock_irqsave(&mimio->txlock, flags);
	mimio->txflags |= MIMIO_TXDONE;
	spin_unlock_irqrestore(&mimio->txlock, flags);
	wmb();
	wake_up(&mimio->waitq);
}