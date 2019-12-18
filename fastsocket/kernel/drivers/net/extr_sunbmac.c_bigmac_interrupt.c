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
typedef  int u32 ;
struct bigmac {scalar_t__ gregs; scalar_t__ creg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CREG_STAT ; 
 int CREG_STAT_ERRORS ; 
 int CREG_STAT_RXIRQ ; 
 int CREG_STAT_TXIRQ ; 
 int /*<<< orphan*/  DIRQ (char*) ; 
 scalar_t__ GLOB_STAT ; 
 int GLOB_STAT_BM ; 
 int GLOB_STAT_ER ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bigmac_is_medium_rare (struct bigmac*,int,int) ; 
 int /*<<< orphan*/  bigmac_rx (struct bigmac*) ; 
 int /*<<< orphan*/  bigmac_tx (struct bigmac*) ; 
 int sbus_readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t bigmac_interrupt(int irq, void *dev_id)
{
	struct bigmac *bp = (struct bigmac *) dev_id;
	u32 qec_status, bmac_status;

	DIRQ(("bigmac_interrupt: "));

	/* Latch status registers now. */
	bmac_status = sbus_readl(bp->creg + CREG_STAT);
	qec_status = sbus_readl(bp->gregs + GLOB_STAT);

	DIRQ(("qec_status=%08x bmac_status=%08x\n", qec_status, bmac_status));
	if ((qec_status & (GLOB_STAT_ER | GLOB_STAT_BM)) ||
	   (bmac_status & CREG_STAT_ERRORS))
		bigmac_is_medium_rare(bp, qec_status, bmac_status);

	if (bmac_status & CREG_STAT_TXIRQ)
		bigmac_tx(bp);

	if (bmac_status & CREG_STAT_RXIRQ)
		bigmac_rx(bp);

	return IRQ_HANDLED;
}