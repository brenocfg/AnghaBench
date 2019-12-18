#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * the_controller ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int vhci_hcd_remove(struct platform_device *pdev)
{
	struct usb_hcd	*hcd;

	hcd = platform_get_drvdata(pdev);
	if (!hcd)
		return 0;

	/*
	 * Disconnects the root hub,
	 * then reverses the effects of usb_add_hcd(),
	 * invoking the HCD's stop() methods.
	 */
	usb_remove_hcd(hcd);
	usb_put_hcd(hcd);
	the_controller = NULL;


	return 0;
}