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
struct pxa_udc {int enabled; int /*<<< orphan*/ * pxa_ep; int /*<<< orphan*/  dev; int /*<<< orphan*/  stats; TYPE_1__ gadget; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCR ; 
 int UDCCR_EMCE ; 
 int /*<<< orphan*/  UDCCR_UDE ; 
 int /*<<< orphan*/  UDCCSR0_ACM ; 
 int /*<<< orphan*/  UDCICR0 ; 
 int /*<<< orphan*/  UDCICR1 ; 
 int UDCICR1_IECC ; 
 int UDCICR1_IERS ; 
 int UDCICR1_IERU ; 
 int UDCICR1_IESU ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ep0_idle (struct pxa_udc*) ; 
 int /*<<< orphan*/  ep_write_UDCCSR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pio_irq_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_clear_mask_UDCCR (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_set_mask_UDCCR (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writel (struct pxa_udc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void udc_enable(struct pxa_udc *udc)
{
	if (udc->enabled)
		return;

	udc_writel(udc, UDCICR0, 0);
	udc_writel(udc, UDCICR1, 0);
	udc_clear_mask_UDCCR(udc, UDCCR_UDE);

	clk_enable(udc->clk);

	ep0_idle(udc);
	udc->gadget.speed = USB_SPEED_FULL;
	memset(&udc->stats, 0, sizeof(udc->stats));

	udc_set_mask_UDCCR(udc, UDCCR_UDE);
	ep_write_UDCCSR(&udc->pxa_ep[0], UDCCSR0_ACM);
	udelay(2);
	if (udc_readl(udc, UDCCR) & UDCCR_EMCE)
		dev_err(udc->dev, "Configuration errors, udc disabled\n");

	/*
	 * Caller must be able to sleep in order to cope with startup transients
	 */
	msleep(100);

	/* enable suspend/resume and reset irqs */
	udc_writel(udc, UDCICR1,
			UDCICR1_IECC | UDCICR1_IERU
			| UDCICR1_IESU | UDCICR1_IERS);

	/* enable ep0 irqs */
	pio_irq_enable(&udc->pxa_ep[0]);

	udc->enabled = 1;
}