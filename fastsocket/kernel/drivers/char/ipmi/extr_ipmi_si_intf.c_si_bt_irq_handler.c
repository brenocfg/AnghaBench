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
struct TYPE_2__ {int /*<<< orphan*/  (* outputb ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;} ;
struct smi_info {TYPE_1__ io; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IPMI_BT_INTMASK_CLEAR_IRQ_BIT ; 
 int IPMI_BT_INTMASK_ENABLE_IRQ_BIT ; 
 int /*<<< orphan*/  IPMI_BT_INTMASK_REG ; 
 int /*<<< orphan*/  si_irq_handler (int,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t si_bt_irq_handler(int irq, void *data)
{
	struct smi_info *smi_info = data;
	/* We need to clear the IRQ flag for the BT interface. */
	smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_REG,
			     IPMI_BT_INTMASK_CLEAR_IRQ_BIT
			     | IPMI_BT_INTMASK_ENABLE_IRQ_BIT);
	return si_irq_handler(irq, data);
}