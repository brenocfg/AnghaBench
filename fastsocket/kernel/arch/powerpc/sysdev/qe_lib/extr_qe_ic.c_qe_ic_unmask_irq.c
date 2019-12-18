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
struct qe_ic {int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  mask_reg; } ;

/* Variables and functions */
 struct qe_ic* qe_ic_from_irq (unsigned int) ; 
 TYPE_1__* qe_ic_info ; 
 int /*<<< orphan*/  qe_ic_lock ; 
 int qe_ic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int virq_to_hw (unsigned int) ; 

__attribute__((used)) static void qe_ic_unmask_irq(unsigned int virq)
{
	struct qe_ic *qe_ic = qe_ic_from_irq(virq);
	unsigned int src = virq_to_hw(virq);
	unsigned long flags;
	u32 temp;

	spin_lock_irqsave(&qe_ic_lock, flags);

	temp = qe_ic_read(qe_ic->regs, qe_ic_info[src].mask_reg);
	qe_ic_write(qe_ic->regs, qe_ic_info[src].mask_reg,
		    temp | qe_ic_info[src].mask);

	spin_unlock_irqrestore(&qe_ic_lock, flags);
}