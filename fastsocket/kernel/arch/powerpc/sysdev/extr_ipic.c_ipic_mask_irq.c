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
typedef  int u32 ;
struct ipic {int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int bit; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 struct ipic* ipic_from_irq (unsigned int) ; 
 TYPE_1__* ipic_info ; 
 unsigned int ipic_irq_to_hw (unsigned int) ; 
 int /*<<< orphan*/  ipic_lock ; 
 int ipic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipic_mask_irq(unsigned int virq)
{
	struct ipic *ipic = ipic_from_irq(virq);
	unsigned int src = ipic_irq_to_hw(virq);
	unsigned long flags;
	u32 temp;

	spin_lock_irqsave(&ipic_lock, flags);

	temp = ipic_read(ipic->regs, ipic_info[src].mask);
	temp &= ~(1 << (31 - ipic_info[src].bit));
	ipic_write(ipic->regs, ipic_info[src].mask, temp);

	/* mb() can't guarantee that masking is finished.  But it does finish
	 * for nearly all cases. */
	mb();

	spin_unlock_irqrestore(&ipic_lock, flags);
}