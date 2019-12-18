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
struct TYPE_2__ {int /*<<< orphan*/  state; struct usb_bus* host; } ;
struct twl4030_usb {TYPE_1__ otg; } ;
struct otg_transceiver {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 struct twl4030_usb* xceiv_to_twl (struct otg_transceiver*) ; 

__attribute__((used)) static int twl4030_set_host(struct otg_transceiver *x, struct usb_bus *host)
{
	struct twl4030_usb *twl;

	if (!x)
		return -ENODEV;

	twl = xceiv_to_twl(x);
	twl->otg.host = host;
	if (!host)
		twl->otg.state = OTG_STATE_UNDEFINED;

	return 0;
}