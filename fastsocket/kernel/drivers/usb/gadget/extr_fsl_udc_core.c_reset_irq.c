#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ a_alt_hnp_support; scalar_t__ a_hnp_support; scalar_t__ b_hnp_enable; } ;
struct fsl_udc {int /*<<< orphan*/  usb_state; TYPE_1__ gadget; scalar_t__ remote_wakeup; int /*<<< orphan*/  ep0_state; scalar_t__ ep0_dir; scalar_t__ resume_state; scalar_t__ device_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  portsc1; int /*<<< orphan*/  endptflush; int /*<<< orphan*/  endpointprime; int /*<<< orphan*/  endptcomplete; int /*<<< orphan*/  endptsetupstat; int /*<<< orphan*/  deviceaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int PORTSCX_PORT_RESET ; 
 int USB_DEVICE_ADDRESS_MASK ; 
 int /*<<< orphan*/  USB_STATE_ATTACHED ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  VDBG (char*) ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dr_controller_run (struct fsl_udc*) ; 
 int /*<<< orphan*/  dr_controller_setup (struct fsl_udc*) ; 
 TYPE_2__* dr_regs ; 
 int /*<<< orphan*/  ep0_setup (struct fsl_udc*) ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (int,int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int /*<<< orphan*/  reset_queues (struct fsl_udc*) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static void reset_irq(struct fsl_udc *udc)
{
	u32 temp;
	unsigned long timeout;

	/* Clear the device address */
	temp = fsl_readl(&dr_regs->deviceaddr);
	fsl_writel(temp & ~USB_DEVICE_ADDRESS_MASK, &dr_regs->deviceaddr);

	udc->device_address = 0;

	/* Clear usb state */
	udc->resume_state = 0;
	udc->ep0_dir = 0;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->remote_wakeup = 0;	/* default to 0 on reset */
	udc->gadget.b_hnp_enable = 0;
	udc->gadget.a_hnp_support = 0;
	udc->gadget.a_alt_hnp_support = 0;

	/* Clear all the setup token semaphores */
	temp = fsl_readl(&dr_regs->endptsetupstat);
	fsl_writel(temp, &dr_regs->endptsetupstat);

	/* Clear all the endpoint complete status bits */
	temp = fsl_readl(&dr_regs->endptcomplete);
	fsl_writel(temp, &dr_regs->endptcomplete);

	timeout = jiffies + 100;
	while (fsl_readl(&dr_regs->endpointprime)) {
		/* Wait until all endptprime bits cleared */
		if (time_after(jiffies, timeout)) {
			ERR("Timeout for reset\n");
			break;
		}
		cpu_relax();
	}

	/* Write 1s to the flush register */
	fsl_writel(0xffffffff, &dr_regs->endptflush);

	if (fsl_readl(&dr_regs->portsc1) & PORTSCX_PORT_RESET) {
		VDBG("Bus reset");
		/* Reset all the queues, include XD, dTD, EP queue
		 * head and TR Queue */
		reset_queues(udc);
		udc->usb_state = USB_STATE_DEFAULT;
	} else {
		VDBG("Controller reset");
		/* initialize usb hw reg except for regs for EP, not
		 * touch usbintr reg */
		dr_controller_setup(udc);

		/* Reset all internal used Queues */
		reset_queues(udc);

		ep0_setup(udc);

		/* Enable DR IRQ reg, Set Run bit, change udc state */
		dr_controller_run(udc);
		udc->usb_state = USB_STATE_ATTACHED;
	}
}