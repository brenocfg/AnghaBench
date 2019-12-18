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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ohci_stop (struct usb_hcd*) ; 
 int /*<<< orphan*/  omap_ohci_clock_power (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ohci_omap_stop(struct usb_hcd *hcd)
{
	dev_dbg(hcd->self.controller, "stopping USB Controller\n");
	ohci_stop(hcd);
	omap_ohci_clock_power(0);
}