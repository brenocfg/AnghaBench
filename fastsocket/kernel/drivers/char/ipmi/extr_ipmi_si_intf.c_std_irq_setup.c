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
struct TYPE_2__ {int /*<<< orphan*/  (* outputb ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct smi_info {scalar_t__ si_type; scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_cleanup; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  IPMI_BT_INTMASK_ENABLE_IRQ_BIT ; 
 int /*<<< orphan*/  IPMI_BT_INTMASK_REG ; 
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 scalar_t__ SI_BT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct smi_info*) ; 
 int /*<<< orphan*/  si_bt_irq_handler ; 
 int /*<<< orphan*/  si_irq_handler ; 
 int /*<<< orphan*/  std_irq_cleanup ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int std_irq_setup(struct smi_info *info)
{
	int rv;

	if (!info->irq)
		return 0;

	if (info->si_type == SI_BT) {
		rv = request_irq(info->irq,
				 si_bt_irq_handler,
				 IRQF_SHARED | IRQF_DISABLED,
				 DEVICE_NAME,
				 info);
		if (!rv)
			/* Enable the interrupt in the BT interface. */
			info->io.outputb(&info->io, IPMI_BT_INTMASK_REG,
					 IPMI_BT_INTMASK_ENABLE_IRQ_BIT);
	} else
		rv = request_irq(info->irq,
				 si_irq_handler,
				 IRQF_SHARED | IRQF_DISABLED,
				 DEVICE_NAME,
				 info);
	if (rv) {
		dev_warn(info->dev, "%s unable to claim interrupt %d,"
			 " running polled\n",
			 DEVICE_NAME, info->irq);
		info->irq = 0;
	} else {
		info->irq_cleanup = std_irq_cleanup;
		dev_info(info->dev, "Using irq %d\n", info->irq);
	}

	return rv;
}