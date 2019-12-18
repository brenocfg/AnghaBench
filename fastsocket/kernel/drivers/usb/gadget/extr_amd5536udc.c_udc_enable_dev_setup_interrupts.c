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
struct udc {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  irqmsk; } ;

/* Variables and functions */
 int AMD_UNMASK_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  UDC_DEVINT_ENUM ; 
 int /*<<< orphan*/  UDC_DEVINT_SC ; 
 int /*<<< orphan*/  UDC_DEVINT_SI ; 
 int /*<<< orphan*/  UDC_DEVINT_SVC ; 
 int /*<<< orphan*/  UDC_DEVINT_UR ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udc_enable_dev_setup_interrupts(struct udc *dev)
{
	u32 tmp;

	DBG(dev, "enable device interrupts for setup data\n");

	/* read irq mask */
	tmp = readl(&dev->regs->irqmsk);

	/* enable SET_INTERFACE, SET_CONFIG and other needed irq's */
	tmp &= AMD_UNMASK_BIT(UDC_DEVINT_SI)
		& AMD_UNMASK_BIT(UDC_DEVINT_SC)
		& AMD_UNMASK_BIT(UDC_DEVINT_UR)
		& AMD_UNMASK_BIT(UDC_DEVINT_SVC)
		& AMD_UNMASK_BIT(UDC_DEVINT_ENUM);
	writel(tmp, &dev->regs->irqmsk);

	return 0;
}