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
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct fsl_udc {int /*<<< orphan*/  usb_state; int /*<<< orphan*/  resume_state; TYPE_1__ gadget; } ;
struct TYPE_4__ {int /*<<< orphan*/  portsc1; } ;

/* Variables and functions */
 int PORTSCX_PORT_RESET ; 
#define  PORTSCX_PORT_SPEED_FULL 130 
#define  PORTSCX_PORT_SPEED_HIGH 129 
#define  PORTSCX_PORT_SPEED_LOW 128 
 int PORTSCX_PORT_SPEED_MASK ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_LOW ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 TYPE_2__* dr_regs ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void port_change_irq(struct fsl_udc *udc)
{
	u32 speed;

	/* Bus resetting is finished */
	if (!(fsl_readl(&dr_regs->portsc1) & PORTSCX_PORT_RESET)) {
		/* Get the speed */
		speed = (fsl_readl(&dr_regs->portsc1)
				& PORTSCX_PORT_SPEED_MASK);
		switch (speed) {
		case PORTSCX_PORT_SPEED_HIGH:
			udc->gadget.speed = USB_SPEED_HIGH;
			break;
		case PORTSCX_PORT_SPEED_FULL:
			udc->gadget.speed = USB_SPEED_FULL;
			break;
		case PORTSCX_PORT_SPEED_LOW:
			udc->gadget.speed = USB_SPEED_LOW;
			break;
		default:
			udc->gadget.speed = USB_SPEED_UNKNOWN;
			break;
		}
	}

	/* Update USB state */
	if (!udc->resume_state)
		udc->usb_state = USB_STATE_DEFAULT;
}