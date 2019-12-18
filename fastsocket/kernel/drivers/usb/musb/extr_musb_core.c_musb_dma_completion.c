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
typedef  int u8 ;
struct musb {int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_HM ; 
 int /*<<< orphan*/  is_cppi_enabled () ; 
 scalar_t__ is_host_capable () ; 
 scalar_t__ is_peripheral_capable () ; 
 int /*<<< orphan*/  musb_g_ep0_irq (struct musb*) ; 
 int /*<<< orphan*/  musb_g_rx (struct musb*,int) ; 
 int /*<<< orphan*/  musb_g_tx (struct musb*,int) ; 
 int /*<<< orphan*/  musb_h_ep0_irq (struct musb*) ; 
 int /*<<< orphan*/  musb_host_rx (struct musb*,int) ; 
 int /*<<< orphan*/  musb_host_tx (struct musb*,int) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void musb_dma_completion(struct musb *musb, u8 epnum, u8 transmit)
{
	u8	devctl = musb_readb(musb->mregs, MUSB_DEVCTL);

	/* called with controller lock already held */

	if (!epnum) {
#ifndef CONFIG_USB_TUSB_OMAP_DMA
		if (!is_cppi_enabled()) {
			/* endpoint 0 */
			if (devctl & MUSB_DEVCTL_HM)
				musb_h_ep0_irq(musb);
			else
				musb_g_ep0_irq(musb);
		}
#endif
	} else {
		/* endpoints 1..15 */
		if (transmit) {
			if (devctl & MUSB_DEVCTL_HM) {
				if (is_host_capable())
					musb_host_tx(musb, epnum);
			} else {
				if (is_peripheral_capable())
					musb_g_tx(musb, epnum);
			}
		} else {
			/* receive */
			if (devctl & MUSB_DEVCTL_HM) {
				if (is_host_capable())
					musb_host_rx(musb, epnum);
			} else {
				if (is_peripheral_capable())
					musb_g_rx(musb, epnum);
			}
		}
	}
}