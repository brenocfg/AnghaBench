#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ioc3_driver_data {scalar_t__* active; int /*<<< orphan*/  dual_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {size_t id; int /*<<< orphan*/  (* intr ) (TYPE_1__*,struct ioc3_driver_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 TYPE_1__* ioc3_ethernet ; 
 int /*<<< orphan*/  ioc3_submodules_lock ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct ioc3_driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ioc3_intr_eth(int irq, void *arg)
{
	unsigned long flags;
	struct ioc3_driver_data *idd = (struct ioc3_driver_data *)arg;
	int handled = 1;

	if(!idd->dual_irq)
		return IRQ_NONE;
	read_lock_irqsave(&ioc3_submodules_lock, flags);
	if(ioc3_ethernet && idd->active[ioc3_ethernet->id]
				&& ioc3_ethernet->intr)
		handled = handled && !ioc3_ethernet->intr(ioc3_ethernet, idd, 0);
	read_unlock_irqrestore(&ioc3_submodules_lock, flags);
	return handled?IRQ_HANDLED:IRQ_NONE;
}