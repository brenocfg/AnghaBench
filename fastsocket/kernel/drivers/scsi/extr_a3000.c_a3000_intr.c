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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {unsigned int ISTR; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 TYPE_3__* DMA (TYPE_1__*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int ISTR_INTS ; 
 unsigned int ISTR_INT_P ; 
 TYPE_1__* a3000_host ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wd33c93_intr (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t a3000_intr (int irq, void *dummy)
{
	unsigned long flags;
	unsigned int status = DMA(a3000_host)->ISTR;

	if (!(status & ISTR_INT_P))
		return IRQ_NONE;
	if (status & ISTR_INTS)
	{
		spin_lock_irqsave(a3000_host->host_lock, flags);
		wd33c93_intr (a3000_host);
		spin_unlock_irqrestore(a3000_host->host_lock, flags);
		return IRQ_HANDLED;
	}
	printk("Non-serviced A3000 SCSI-interrupt? ISTR = %02x\n", status);
	return IRQ_NONE;
}