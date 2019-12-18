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
struct usb_gadget {int dummy; } ;
struct pxa_udc {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  UDCCR ; 
 int UDCCR_DWRE ; 
 int /*<<< orphan*/  UDCCR_UDR ; 
 struct pxa_udc* to_gadget_udc (struct usb_gadget*) ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_set_mask_UDCCR (struct pxa_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_udc_wakeup(struct usb_gadget *_gadget)
{
	struct pxa_udc *udc = to_gadget_udc(_gadget);

	/* host may not have enabled remote wakeup */
	if ((udc_readl(udc, UDCCR) & UDCCR_DWRE) == 0)
		return -EHOSTUNREACH;
	udc_set_mask_UDCCR(udc, UDCCR_UDR);
	return 0;
}