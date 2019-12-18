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
struct musb {int /*<<< orphan*/  lock; void* int_rx; int /*<<< orphan*/  mregs; void* int_tx; scalar_t__ int_usb; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int /*<<< orphan*/  MUSB_INTRRX ; 
 int /*<<< orphan*/  MUSB_INTRTX ; 
 int /*<<< orphan*/  MUSB_INTRUSB ; 
 scalar_t__ musb_interrupt (struct musb*) ; 
 scalar_t__ musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* musb_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  musb_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t blackfin_interrupt(int irq, void *__hci)
{
	unsigned long	flags;
	irqreturn_t	retval = IRQ_NONE;
	struct musb	*musb = __hci;

	spin_lock_irqsave(&musb->lock, flags);

	musb->int_usb = musb_readb(musb->mregs, MUSB_INTRUSB);
	musb->int_tx = musb_readw(musb->mregs, MUSB_INTRTX);
	musb->int_rx = musb_readw(musb->mregs, MUSB_INTRRX);

	if (musb->int_usb || musb->int_tx || musb->int_rx) {
		musb_writeb(musb->mregs, MUSB_INTRUSB, musb->int_usb);
		musb_writew(musb->mregs, MUSB_INTRTX, musb->int_tx);
		musb_writew(musb->mregs, MUSB_INTRRX, musb->int_rx);
		retval = musb_interrupt(musb);
	}

	spin_unlock_irqrestore(&musb->lock, flags);

	/* REVISIT we sometimes get spurious IRQs on g_ep0
	 * not clear why... fall in BF54x too.
	 */
	if (retval != IRQ_HANDLED)
		DBG(5, "spurious?\n");

	return IRQ_HANDLED;
}