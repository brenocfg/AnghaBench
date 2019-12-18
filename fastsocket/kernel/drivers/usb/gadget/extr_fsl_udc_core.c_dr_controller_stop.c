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
struct fsl_udc {int stopped; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbcmd; int /*<<< orphan*/  usbintr; } ;

/* Variables and functions */
 unsigned int USB_CMD_RUN_STOP ; 
 TYPE_1__* dr_regs ; 
 unsigned int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_controller_stop(struct fsl_udc *udc)
{
	unsigned int tmp;

	/* disable all INTR */
	fsl_writel(0, &dr_regs->usbintr);

	/* Set stopped bit for isr */
	udc->stopped = 1;

	/* disable IO output */
/*	usb_sys_regs->control = 0; */

	/* set controller to Stop */
	tmp = fsl_readl(&dr_regs->usbcmd);
	tmp &= ~USB_CMD_RUN_STOP;
	fsl_writel(tmp, &dr_regs->usbcmd);

	return;
}