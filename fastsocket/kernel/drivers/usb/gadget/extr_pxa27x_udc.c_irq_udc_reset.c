#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  irqs_reset; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct pxa_udc {TYPE_2__ stats; TYPE_1__ gadget; int /*<<< orphan*/  driver; int /*<<< orphan*/  dev; struct pxa_ep* pxa_ep; } ;
struct pxa_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  UDCCR ; 
 int UDCCR_UDA ; 
 int UDCCSR0_FTF ; 
 int UDCCSR0_OPC ; 
 int /*<<< orphan*/  UDCISR1 ; 
 int /*<<< orphan*/  UDCISR1_IRRS ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ep0_idle (struct pxa_udc*) ; 
 int /*<<< orphan*/  ep_write_UDCCSR (struct pxa_ep*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nuke (struct pxa_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_activity (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writel (struct pxa_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irq_udc_reset(struct pxa_udc *udc)
{
	u32 udccr = udc_readl(udc, UDCCR);
	struct pxa_ep *ep = &udc->pxa_ep[0];

	dev_info(udc->dev, "USB reset\n");
	udc_writel(udc, UDCISR1, UDCISR1_IRRS);
	udc->stats.irqs_reset++;

	if ((udccr & UDCCR_UDA) == 0) {
		dev_dbg(udc->dev, "USB reset start\n");
		stop_activity(udc, udc->driver);
	}
	udc->gadget.speed = USB_SPEED_FULL;
	memset(&udc->stats, 0, sizeof udc->stats);

	nuke(ep, -EPROTO);
	ep_write_UDCCSR(ep, UDCCSR0_FTF | UDCCSR0_OPC);
	ep0_idle(udc);
}