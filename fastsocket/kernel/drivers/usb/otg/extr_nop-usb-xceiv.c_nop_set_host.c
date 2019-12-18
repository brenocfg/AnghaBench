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
struct usb_bus {int dummy; } ;
struct otg_transceiver {int dummy; } ;
struct TYPE_2__ {struct usb_bus* host; } ;
struct nop_usb_xceiv {TYPE_1__ otg; } ;

/* Variables and functions */
 int ENODEV ; 
 struct nop_usb_xceiv* xceiv_to_nop (struct otg_transceiver*) ; 

__attribute__((used)) static int nop_set_host(struct otg_transceiver *x, struct usb_bus *host)
{
	struct nop_usb_xceiv *nop;

	if (!x)
		return -ENODEV;

	nop = xceiv_to_nop(x);

	if (!host) {
		nop->otg.host = NULL;
		return -ENODEV;
	}

	nop->otg.host = host;
	return 0;
}