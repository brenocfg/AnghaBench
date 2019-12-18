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

/* Variables and functions */
 unsigned int NR_IRQS ; 
 int cc_get_imsk_other (int) ; 
 int /*<<< orphan*/  cc_set_imsk_other (int,int) ; 
 int* sbus_tid ; 
 int* sbus_to_pil ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun4d_imsk_lock ; 

__attribute__((used)) static void sun4d_enable_irq(unsigned int irq)
{
	int tid = sbus_tid[(irq >> 5) - 1];
	unsigned long flags;
	
	if (irq < NR_IRQS)
		return;

	spin_lock_irqsave(&sun4d_imsk_lock, flags);
	cc_set_imsk_other(tid, cc_get_imsk_other(tid) & ~(1 << sbus_to_pil[(irq >> 2) & 7]));
	spin_unlock_irqrestore(&sun4d_imsk_lock, flags);
}