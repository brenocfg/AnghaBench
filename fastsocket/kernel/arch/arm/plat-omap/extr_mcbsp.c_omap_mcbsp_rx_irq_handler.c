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
 int RSYNC_ERR ; 
 int /*<<< orphan*/  SPCR1 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static irqreturn_t omap_mcbsp_rx_irq_handler(int irq, void *dev_id)
{
	struct omap_mcbsp *mcbsp_rx = dev_id;
	u16 irqst_spcr1;

	irqst_spcr1 = OMAP_MCBSP_READ(mcbsp_rx->io_base, SPCR1);
	dev_dbg(mcbsp_rx->dev, "RX IRQ callback : 0x%x\n", irqst_spcr1);

	if (irqst_spcr1 & RSYNC_ERR) {
		dev_err(mcbsp_rx->dev, "RX Frame Sync Error! : 0x%x\n",
			irqst_spcr1);
		/* Writing zero to RSYNC_ERR clears the IRQ */
		OMAP_MCBSP_WRITE(mcbsp_rx->io_base, SPCR1,
			irqst_spcr1 & ~(RSYNC_ERR));
	} else {
		complete(&mcbsp_rx->tx_irq_completion);
	}

	return IRQ_HANDLED;
}