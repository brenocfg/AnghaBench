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
struct usb_gadget {int dummy; } ;
struct otg_transceiver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; struct usb_gadget* gadget; } ;
struct nop_usb_xceiv {TYPE_1__ otg; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 struct nop_usb_xceiv* xceiv_to_nop (struct otg_transceiver*) ; 

__attribute__((used)) static int nop_set_peripheral(struct otg_transceiver *x,
		struct usb_gadget *gadget)
{
	struct nop_usb_xceiv *nop;

	if (!x)
		return -ENODEV;

	nop = xceiv_to_nop(x);

	if (!gadget) {
		nop->otg.gadget = NULL;
		return -ENODEV;
	}

	nop->otg.gadget = gadget;
	nop->otg.state = OTG_STATE_B_IDLE;
	return 0;
}