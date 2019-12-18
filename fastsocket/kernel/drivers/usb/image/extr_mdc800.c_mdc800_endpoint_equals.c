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
struct usb_endpoint_descriptor {scalar_t__ bEndpointAddress; scalar_t__ bmAttributes; scalar_t__ wMaxPacketSize; } ;

/* Variables and functions */

__attribute__((used)) static int mdc800_endpoint_equals (struct usb_endpoint_descriptor *a,struct usb_endpoint_descriptor *b)
{
	return (
		   ( a->bEndpointAddress == b->bEndpointAddress )
		&& ( a->bmAttributes     == b->bmAttributes     )
		&& ( a->wMaxPacketSize   == b->wMaxPacketSize   )
	);
}