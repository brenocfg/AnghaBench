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
struct qe_udc {TYPE_1__* usb_regs; } ;
struct qe_ep {int epnum; struct qe_udc* udc; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_uscom; } ;

/* Variables and functions */
 int USB_CMD_EP_MASK ; 
 int USB_CMD_STR_FIFO ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qe_ep_filltxfifo(struct qe_ep *ep)
{
	struct qe_udc *udc = ep->udc;

	out_8(&udc->usb_regs->usb_uscom,
			USB_CMD_STR_FIFO | (USB_CMD_EP_MASK & (ep->epnum)));
	return 0;
}