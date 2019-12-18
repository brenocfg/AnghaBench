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
struct udc_usb_ep {int /*<<< orphan*/  desc; } ;
struct pxa_ep {scalar_t__ addr; scalar_t__ dir_in; scalar_t__ type; int config; int interface; int alternate; } ;

/* Variables and functions */
 scalar_t__ usb_endpoint_dir_in (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_num (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_match_usb_pxa(struct udc_usb_ep *udc_usb_ep, struct pxa_ep *ep,
		int config, int interface, int altsetting)
{
	if (usb_endpoint_num(&udc_usb_ep->desc) != ep->addr)
		return 0;
	if (usb_endpoint_dir_in(&udc_usb_ep->desc) != ep->dir_in)
		return 0;
	if (usb_endpoint_type(&udc_usb_ep->desc) != ep->type)
		return 0;
	if ((ep->config != config) || (ep->interface != interface)
			|| (ep->alternate != altsetting))
		return 0;
	return 1;
}