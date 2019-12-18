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
struct omap_mcbsp {int /*<<< orphan*/  tx_irq_completion; int /*<<< orphan*/  io_base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OMAP_MCBSP_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_MCBSP_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPCR2 ; 
 int XSYNC_ERR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static irqreturn_t omap_mcbsp_tx_irq_handler(int irq, void *dev_id)
{
	struct omap_mcbsp *mcbsp_tx = dev_id;
	u16 irqst_spcr2;

	irqst_spcr2 = OMAP_MCBSP_READ(mcbsp_tx->io_base, SPCR2);
	dev_dbg(mcbsp_tx->dev, "TX IRQ callback : 0x%x\n", irqst_spcr2);

	if (irqst_spcr2 & XSYNC_ERR) {
		dev_err(mcbsp_tx->dev, "TX Frame Sync Error! : 0x%x\n",
			irqst_spcr2);
		/* Writing zero to XSYNC_ERR clears the IRQ */
		OMAP_MCBSP_WRITE(mcbsp_tx->io_base, SPCR2,
			irqst_spcr2 & ~(XSYNC_ERR));
	} else {
		complete(&mcbsp_tx->tx_irq_completion);
	}

	return IRQ_HANDLED;
}