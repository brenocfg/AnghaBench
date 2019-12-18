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
typedef  int u32 ;
struct pxa_udc {struct pxa_ep* pxa_ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  irqs; } ;
struct pxa_ep {TYPE_1__ stats; } ;

/* Variables and functions */
 int UDCCISR0_EP_MASK ; 
 int UDCCISR1_EP_MASK ; 
 int UDCICR_FIFOERR ; 
 int UDCICR_PKTCOMPL ; 
 int /*<<< orphan*/  UDCISR0 ; 
 int /*<<< orphan*/  UDCISR1 ; 
 int /*<<< orphan*/  UDCISR_INT (int,int) ; 
 int UDCISR_INT_MASK ; 
 int /*<<< orphan*/  handle_ep (struct pxa_ep*) ; 
 int /*<<< orphan*/  handle_ep0 (struct pxa_udc*,int,int) ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writel (struct pxa_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irq_handle_data(int irq, struct pxa_udc *udc)
{
	int i;
	struct pxa_ep *ep;
	u32 udcisr0 = udc_readl(udc, UDCISR0) & UDCCISR0_EP_MASK;
	u32 udcisr1 = udc_readl(udc, UDCISR1) & UDCCISR1_EP_MASK;

	if (udcisr0 & UDCISR_INT_MASK) {
		udc->pxa_ep[0].stats.irqs++;
		udc_writel(udc, UDCISR0, UDCISR_INT(0, UDCISR_INT_MASK));
		handle_ep0(udc, !!(udcisr0 & UDCICR_FIFOERR),
				!!(udcisr0 & UDCICR_PKTCOMPL));
	}

	udcisr0 >>= 2;
	for (i = 1; udcisr0 != 0 && i < 16; udcisr0 >>= 2, i++) {
		if (!(udcisr0 & UDCISR_INT_MASK))
			continue;

		udc_writel(udc, UDCISR0, UDCISR_INT(i, UDCISR_INT_MASK));
		ep = &udc->pxa_ep[i];
		ep->stats.irqs++;
		handle_ep(ep);
	}

	for (i = 16; udcisr1 != 0 && i < 24; udcisr1 >>= 2, i++) {
		udc_writel(udc, UDCISR1, UDCISR_INT(i - 16, UDCISR_INT_MASK));
		if (!(udcisr1 & UDCISR_INT_MASK))
			continue;

		ep = &udc->pxa_ep[i];
		ep->stats.irqs++;
		handle_ep(ep);
	}

}