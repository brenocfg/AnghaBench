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
struct usb_request {int dummy; } ;
struct musb_hw_ep {int /*<<< orphan*/  ep_in; } ;

/* Variables and functions */
 struct usb_request* next_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct usb_request *next_in_request(struct musb_hw_ep *hw_ep)
{
#ifdef CONFIG_USB_GADGET_MUSB_HDRC
	return next_request(&hw_ep->ep_in);
#else
	return NULL;
#endif
}