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
struct TYPE_4__ {scalar_t__ mode; } ;
struct slgt_info {int rx_restart; int rx_enabled; TYPE_2__ params; TYPE_1__* rbufs; scalar_t__ rx_pio; } ;
struct TYPE_3__ {scalar_t__ pdesc; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 unsigned short BIT1 ; 
 unsigned short BIT14 ; 
 unsigned short BIT2 ; 
 scalar_t__ BIT6 ; 
 unsigned short IRQ_RXDATA ; 
 unsigned short IRQ_RXOVER ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  RDCSR ; 
 int /*<<< orphan*/  RDDAR ; 
 int /*<<< orphan*/  SCR ; 
 int /*<<< orphan*/  SSR ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_reset (struct slgt_info*) ; 
 int /*<<< orphan*/  reset_rbufs (struct slgt_info*) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  slgt_irq_on (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rx_start(struct slgt_info *info)
{
	unsigned short val;

	slgt_irq_off(info, IRQ_RXOVER + IRQ_RXDATA);

	/* clear pending rx overrun IRQ */
	wr_reg16(info, SSR, IRQ_RXOVER);

	/* reset and disable receiver */
	val = rd_reg16(info, RCR) & ~BIT1; /* clear enable bit */
	wr_reg16(info, RCR, (unsigned short)(val | BIT2)); /* set reset bit */
	wr_reg16(info, RCR, val);                  /* clear reset bit */

	rdma_reset(info);
	reset_rbufs(info);

	if (info->rx_pio) {
		/* rx request when rx FIFO not empty */
		wr_reg16(info, SCR, (unsigned short)(rd_reg16(info, SCR) & ~BIT14));
		slgt_irq_on(info, IRQ_RXDATA);
		if (info->params.mode == MGSL_MODE_ASYNC) {
			/* enable saving of rx status */
			wr_reg32(info, RDCSR, BIT6);
		}
	} else {
		/* rx request when rx FIFO half full */
		wr_reg16(info, SCR, (unsigned short)(rd_reg16(info, SCR) | BIT14));
		/* set 1st descriptor address */
		wr_reg32(info, RDDAR, info->rbufs[0].pdesc);

		if (info->params.mode != MGSL_MODE_ASYNC) {
			/* enable rx DMA and DMA interrupt */
			wr_reg32(info, RDCSR, (BIT2 + BIT0));
		} else {
			/* enable saving of rx status, rx DMA and DMA interrupt */
			wr_reg32(info, RDCSR, (BIT6 + BIT2 + BIT0));
		}
	}

	slgt_irq_on(info, IRQ_RXOVER);

	/* enable receiver */
	wr_reg16(info, RCR, (unsigned short)(rd_reg16(info, RCR) | BIT1));

	info->rx_restart = false;
	info->rx_enabled = true;
}