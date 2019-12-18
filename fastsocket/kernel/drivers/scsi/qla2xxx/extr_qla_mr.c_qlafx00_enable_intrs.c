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
struct qla_hw_data {int interrupts_on; int /*<<< orphan*/  hardware_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLAFX00_ENABLE_ICNTRL_REG (struct qla_hw_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
qlafx00_enable_intrs(struct qla_hw_data *ha)
{
	unsigned long flags = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->interrupts_on = 1;
	QLAFX00_ENABLE_ICNTRL_REG(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
}