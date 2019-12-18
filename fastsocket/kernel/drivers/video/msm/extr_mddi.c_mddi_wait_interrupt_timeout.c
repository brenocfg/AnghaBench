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
typedef  int uint32_t ;
struct mddi_info {int got_int; int int_enable; int /*<<< orphan*/  int_wait; int /*<<< orphan*/  int_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEN ; 
 int /*<<< orphan*/  mddi_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static long mddi_wait_interrupt_timeout(struct mddi_info *mddi,
					uint32_t intmask, int timeout)
{
	unsigned long irq_flags;

	spin_lock_irqsave(&mddi->int_lock, irq_flags);
	mddi->got_int &= ~intmask;
	mddi->int_enable |= intmask;
	mddi_writel(mddi->int_enable, INTEN);
	spin_unlock_irqrestore(&mddi->int_lock, irq_flags);
	return wait_event_timeout(mddi->int_wait, mddi->got_int & intmask,
				  timeout);
}