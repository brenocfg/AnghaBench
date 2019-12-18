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
struct musb_hw_ep {int max_packet_sz_tx; int max_packet_sz_rx; int is_shared_fifo; } ;
struct musb {int epmask; int /*<<< orphan*/  nr_endpoints; void* mregs; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MUSB_EP_OFFSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB_FIFOSIZE ; 
 int musb_readb (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int musb_read_fifosize(struct musb *musb,
		struct musb_hw_ep *hw_ep, u8 epnum)
{
	void *mbase = musb->mregs;
	u8 reg = 0;

	/* read from core using indexed model */
	reg = musb_readb(mbase, MUSB_EP_OFFSET(epnum, MUSB_FIFOSIZE));
	/* 0's returned when no more endpoints */
	if (!reg)
		return -ENODEV;

	musb->nr_endpoints++;
	musb->epmask |= (1 << epnum);

	hw_ep->max_packet_sz_tx = 1 << (reg & 0x0f);

	/* shared TX/RX FIFO? */
	if ((reg & 0xf0) == 0xf0) {
		hw_ep->max_packet_sz_rx = hw_ep->max_packet_sz_tx;
		hw_ep->is_shared_fifo = true;
		return 0;
	} else {
		hw_ep->max_packet_sz_rx = 1 << ((reg & 0xf0) >> 4);
		hw_ep->is_shared_fifo = false;
	}

	return 0;
}