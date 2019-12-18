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
struct musb_hw_ep {int /*<<< orphan*/  regs; scalar_t__ epnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_CSR0 ; 
 int MUSB_CSR0_H_SETUPPKT ; 
 int MUSB_CSR0_TXPKTRDY ; 
 int /*<<< orphan*/  MUSB_TXCSR ; 
 int MUSB_TXCSR_H_WZC_BITS ; 
 int MUSB_TXCSR_TXPKTRDY ; 
 int musb_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void musb_h_tx_start(struct musb_hw_ep *ep)
{
	u16	txcsr;

	/* NOTE: no locks here; caller should lock and select EP */
	if (ep->epnum) {
		txcsr = musb_readw(ep->regs, MUSB_TXCSR);
		txcsr |= MUSB_TXCSR_TXPKTRDY | MUSB_TXCSR_H_WZC_BITS;
		musb_writew(ep->regs, MUSB_TXCSR, txcsr);
	} else {
		txcsr = MUSB_CSR0_H_SETUPPKT | MUSB_CSR0_TXPKTRDY;
		musb_writew(ep->regs, MUSB_CSR0, txcsr);
	}

}