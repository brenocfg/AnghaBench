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

/* Variables and functions */
 int /*<<< orphan*/  usbip_uerr (char*) ; 

__attribute__((used)) static int vhci_get_frame_number(struct usb_hcd *hcd)
{
	usbip_uerr("Not yet implemented\n");
	return 0;
}