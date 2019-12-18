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
typedef  int u16 ;
struct omap_udc {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int UDC_DS_CHG ; 
 int UDC_EP0_RX ; 
 int UDC_EP0_TX ; 
 int UDC_EPN_RX ; 
 int UDC_EPN_TX ; 
 int UDC_IRQ_SOF ; 
 int /*<<< orphan*/  UDC_IRQ_SRC ; 
 int UDC_RXN_CNT ; 
 int UDC_RXN_EOT ; 
 int UDC_SETUP ; 
 int UDC_TXN_DONE ; 
 int /*<<< orphan*/  devstate_irq (void*,int) ; 
 int /*<<< orphan*/  dma_irq (void*,int) ; 
 int /*<<< orphan*/  ep0_irq (void*,int) ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static irqreturn_t omap_udc_irq(int irq, void *_udc)
{
	struct omap_udc	*udc = _udc;
	u16		irq_src;
	irqreturn_t	status = IRQ_NONE;
	unsigned long	flags;

	spin_lock_irqsave(&udc->lock, flags);
	irq_src = omap_readw(UDC_IRQ_SRC);

	/* Device state change (usb ch9 stuff) */
	if (irq_src & UDC_DS_CHG) {
		devstate_irq(_udc, irq_src);
		status = IRQ_HANDLED;
		irq_src &= ~UDC_DS_CHG;
	}

	/* EP0 control transfers */
	if (irq_src & (UDC_EP0_RX|UDC_SETUP|UDC_EP0_TX)) {
		ep0_irq(_udc, irq_src);
		status = IRQ_HANDLED;
		irq_src &= ~(UDC_EP0_RX|UDC_SETUP|UDC_EP0_TX);
	}

	/* DMA transfer completion */
	if (use_dma && (irq_src & (UDC_TXN_DONE|UDC_RXN_CNT|UDC_RXN_EOT))) {
		dma_irq(_udc, irq_src);
		status = IRQ_HANDLED;
		irq_src &= ~(UDC_TXN_DONE|UDC_RXN_CNT|UDC_RXN_EOT);
	}

	irq_src &= ~(UDC_IRQ_SOF | UDC_EPN_TX|UDC_EPN_RX);
	if (irq_src)
		DBG("udc_irq, unhandled %03x\n", irq_src);
	spin_unlock_irqrestore(&udc->lock, flags);

	return status;
}