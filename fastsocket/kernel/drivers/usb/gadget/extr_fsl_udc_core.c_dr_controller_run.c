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
struct fsl_udc {scalar_t__ stopped; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbcmd; int /*<<< orphan*/  usbmode; int /*<<< orphan*/  usbintr; } ;

/* Variables and functions */
 int USB_CMD_RUN_STOP ; 
 int USB_INTR_DEVICE_SUSPEND ; 
 int USB_INTR_ERR_INT_EN ; 
 int USB_INTR_INT_EN ; 
 int USB_INTR_PTC_DETECT_EN ; 
 int USB_INTR_RESET_EN ; 
 int USB_INTR_SYS_ERR_EN ; 
 int USB_MODE_CTRL_MODE_DEVICE ; 
 TYPE_1__* dr_regs ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_controller_run(struct fsl_udc *udc)
{
	u32 temp;

	/* Enable DR irq reg */
	temp = USB_INTR_INT_EN | USB_INTR_ERR_INT_EN
		| USB_INTR_PTC_DETECT_EN | USB_INTR_RESET_EN
		| USB_INTR_DEVICE_SUSPEND | USB_INTR_SYS_ERR_EN;

	fsl_writel(temp, &dr_regs->usbintr);

	/* Clear stopped bit */
	udc->stopped = 0;

	/* Set the controller as device mode */
	temp = fsl_readl(&dr_regs->usbmode);
	temp |= USB_MODE_CTRL_MODE_DEVICE;
	fsl_writel(temp, &dr_regs->usbmode);

	/* Set controller to Run */
	temp = fsl_readl(&dr_regs->usbcmd);
	temp |= USB_CMD_RUN_STOP;
	fsl_writel(temp, &dr_regs->usbcmd);

	return;
}