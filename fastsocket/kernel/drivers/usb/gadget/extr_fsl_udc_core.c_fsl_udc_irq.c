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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct fsl_udc {scalar_t__ usb_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  local_setup_buff; scalar_t__ stopped; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  endptcomplete; int /*<<< orphan*/  endptsetupstat; int /*<<< orphan*/  portsc1; int /*<<< orphan*/  usbsts; int /*<<< orphan*/  usbintr; } ;

/* Variables and functions */
 int EP_SETUP_STATUS_EP0 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PORTSCX_PORT_SUSPEND ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 int USB_STS_ERR ; 
 int USB_STS_INT ; 
 int USB_STS_PORT_CHANGE ; 
 int USB_STS_RESET ; 
 int USB_STS_SOF ; 
 int USB_STS_SUSPEND ; 
 int USB_STS_SYS_ERR ; 
 int /*<<< orphan*/  VDBG (char*,...) ; 
 int /*<<< orphan*/  bus_resume (struct fsl_udc*) ; 
 TYPE_1__* dr_regs ; 
 int /*<<< orphan*/  dtd_complete_irq (struct fsl_udc*) ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_change_irq (struct fsl_udc*) ; 
 int /*<<< orphan*/  reset_irq (struct fsl_udc*) ; 
 int /*<<< orphan*/  setup_received_irq (struct fsl_udc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  suspend_irq (struct fsl_udc*) ; 
 int /*<<< orphan*/  tripwire_handler (struct fsl_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fsl_udc_irq(int irq, void *_udc)
{
	struct fsl_udc *udc = _udc;
	u32 irq_src;
	irqreturn_t status = IRQ_NONE;
	unsigned long flags;

	/* Disable ISR for OTG host mode */
	if (udc->stopped)
		return IRQ_NONE;
	spin_lock_irqsave(&udc->lock, flags);
	irq_src = fsl_readl(&dr_regs->usbsts) & fsl_readl(&dr_regs->usbintr);
	/* Clear notification bits */
	fsl_writel(irq_src, &dr_regs->usbsts);

	/* VDBG("irq_src [0x%8x]", irq_src); */

	/* Need to resume? */
	if (udc->usb_state == USB_STATE_SUSPENDED)
		if ((fsl_readl(&dr_regs->portsc1) & PORTSCX_PORT_SUSPEND) == 0)
			bus_resume(udc);

	/* USB Interrupt */
	if (irq_src & USB_STS_INT) {
		VDBG("Packet int");
		/* Setup package, we only support ep0 as control ep */
		if (fsl_readl(&dr_regs->endptsetupstat) & EP_SETUP_STATUS_EP0) {
			tripwire_handler(udc, 0,
					(u8 *) (&udc->local_setup_buff));
			setup_received_irq(udc, &udc->local_setup_buff);
			status = IRQ_HANDLED;
		}

		/* completion of dtd */
		if (fsl_readl(&dr_regs->endptcomplete)) {
			dtd_complete_irq(udc);
			status = IRQ_HANDLED;
		}
	}

	/* SOF (for ISO transfer) */
	if (irq_src & USB_STS_SOF) {
		status = IRQ_HANDLED;
	}

	/* Port Change */
	if (irq_src & USB_STS_PORT_CHANGE) {
		port_change_irq(udc);
		status = IRQ_HANDLED;
	}

	/* Reset Received */
	if (irq_src & USB_STS_RESET) {
		reset_irq(udc);
		status = IRQ_HANDLED;
	}

	/* Sleep Enable (Suspend) */
	if (irq_src & USB_STS_SUSPEND) {
		suspend_irq(udc);
		status = IRQ_HANDLED;
	}

	if (irq_src & (USB_STS_ERR | USB_STS_SYS_ERR)) {
		VDBG("Error IRQ %x", irq_src);
	}

	spin_unlock_irqrestore(&udc->lock, flags);
	return status;
}