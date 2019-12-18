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
struct usb_endpoint_descriptor {int dummy; } ;

/* Variables and functions */
 int xhci_get_endpoint_index (struct usb_endpoint_descriptor*) ; 

unsigned int xhci_get_endpoint_flag(struct usb_endpoint_descriptor *desc)
{
	return 1 << (xhci_get_endpoint_index(desc) + 1);
}