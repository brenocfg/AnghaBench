#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* controller; } ;
struct usb_hcd {TYPE_2__ self; } ;
struct omap_usb_config {scalar_t__ rwc; scalar_t__ otg; } ;
struct ohci_hcd {TYPE_1__* regs; int /*<<< orphan*/  hc_control; } ;
struct TYPE_6__ {struct omap_usb_config* platform_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_CTRL_RWC ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  host_enabled ; 
 int ohci_run (struct ohci_hcd*) ; 
 int /*<<< orphan*/  ohci_stop (struct usb_hcd*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ohci_omap_start (struct usb_hcd *hcd)
{
	struct omap_usb_config *config;
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	int		ret;

	if (!host_enabled)
		return 0;
	config = hcd->self.controller->platform_data;
	if (config->otg || config->rwc) {
		ohci->hc_control = OHCI_CTRL_RWC;
		writel(OHCI_CTRL_RWC, &ohci->regs->control);
	}

	if ((ret = ohci_run (ohci)) < 0) {
		dev_err(hcd->self.controller, "can't start\n");
		ohci_stop (hcd);
		return ret;
	}
	return 0;
}