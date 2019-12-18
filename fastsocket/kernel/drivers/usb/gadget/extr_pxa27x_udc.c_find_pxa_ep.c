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
struct udc_usb_ep {int dummy; } ;
struct pxa_udc {int config; int last_interface; int last_alternate; struct pxa_ep* pxa_ep; struct udc_usb_ep* udc_usb_ep; } ;
struct pxa_ep {int dummy; } ;

/* Variables and functions */
 int NR_PXA_ENDPOINTS ; 
 scalar_t__ is_match_usb_pxa (struct udc_usb_ep*,struct pxa_ep*,int,int,int) ; 

__attribute__((used)) static struct pxa_ep *find_pxa_ep(struct pxa_udc *udc,
		struct udc_usb_ep *udc_usb_ep)
{
	int i;
	struct pxa_ep *ep;
	int cfg = udc->config;
	int iface = udc->last_interface;
	int alt = udc->last_alternate;

	if (udc_usb_ep == &udc->udc_usb_ep[0])
		return &udc->pxa_ep[0];

	for (i = 1; i < NR_PXA_ENDPOINTS; i++) {
		ep = &udc->pxa_ep[i];
		if (is_match_usb_pxa(udc_usb_ep, ep, cfg, iface, alt))
			return ep;
	}
	return NULL;
}