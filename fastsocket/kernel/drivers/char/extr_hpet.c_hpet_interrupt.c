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
struct hpet_dev {int hd_flags; unsigned long hd_ireqfreq; int /*<<< orphan*/  hd_async_queue; int /*<<< orphan*/  hd_waitqueue; TYPE_3__* hd_hpet; TYPE_2__* hd_timer; int /*<<< orphan*/  hd_irqdata; TYPE_1__* hd_hpets; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  hpet_isr; } ;
struct TYPE_5__ {int /*<<< orphan*/  hpet_compare; } ;
struct TYPE_4__ {struct hpet_dev* hp_dev; } ;

/* Variables and functions */
 int HPET_IE ; 
 int HPET_PERIODIC ; 
 int HPET_SHARED_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  hpet_lock ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long read_counter (int /*<<< orphan*/ *) ; 
 unsigned long readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_counter (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t hpet_interrupt(int irq, void *data)
{
	struct hpet_dev *devp;
	unsigned long isr;

	devp = data;
	isr = 1 << (devp - devp->hd_hpets->hp_dev);

	if ((devp->hd_flags & HPET_SHARED_IRQ) &&
	    !(isr & readl(&devp->hd_hpet->hpet_isr)))
		return IRQ_NONE;

	spin_lock(&hpet_lock);
	devp->hd_irqdata++;

	/*
	 * For non-periodic timers, increment the accumulator.
	 * This has the effect of treating non-periodic like periodic.
	 */
	if ((devp->hd_flags & (HPET_IE | HPET_PERIODIC)) == HPET_IE) {
		unsigned long m, t;

		t = devp->hd_ireqfreq;
		m = read_counter(&devp->hd_timer->hpet_compare);
		write_counter(t + m, &devp->hd_timer->hpet_compare);
	}

	if (devp->hd_flags & HPET_SHARED_IRQ)
		writel(isr, &devp->hd_hpet->hpet_isr);
	spin_unlock(&hpet_lock);

	wake_up_interruptible(&devp->hd_waitqueue);

	kill_fasync(&devp->hd_async_queue, SIGIO, POLL_IN);

	return IRQ_HANDLED;
}