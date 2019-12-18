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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct pxa_udc {scalar_t__ enabled; TYPE_1__ gadget; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCR_UDE ; 
 int /*<<< orphan*/  UDCICR0 ; 
 int /*<<< orphan*/  UDCICR1 ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_idle (struct pxa_udc*) ; 
 int /*<<< orphan*/  udc_clear_mask_UDCCR (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writel (struct pxa_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_disable(struct pxa_udc *udc)
{
	if (!udc->enabled)
		return;

	udc_writel(udc, UDCICR0, 0);
	udc_writel(udc, UDCICR1, 0);

	udc_clear_mask_UDCCR(udc, UDCCR_UDE);
	clk_disable(udc->clk);

	ep0_idle(udc);
	udc->gadget.speed = USB_SPEED_UNKNOWN;

	udc->enabled = 0;
}