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
struct spi_imx_data {int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  (* intctrl ) (struct spi_imx_data*,int /*<<< orphan*/ ) ;scalar_t__ txfifo; scalar_t__ count; int /*<<< orphan*/  (* rx ) (struct spi_imx_data*) ;scalar_t__ (* rx_available ) (struct spi_imx_data*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MXC_INT_RR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_imx_push (struct spi_imx_data*) ; 
 scalar_t__ stub1 (struct spi_imx_data*) ; 
 int /*<<< orphan*/  stub2 (struct spi_imx_data*) ; 
 int /*<<< orphan*/  stub3 (struct spi_imx_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct spi_imx_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t spi_imx_isr(int irq, void *dev_id)
{
	struct spi_imx_data *spi_imx = dev_id;

	while (spi_imx->rx_available(spi_imx)) {
		spi_imx->rx(spi_imx);
		spi_imx->txfifo--;
	}

	if (spi_imx->count) {
		spi_imx_push(spi_imx);
		return IRQ_HANDLED;
	}

	if (spi_imx->txfifo) {
		/* No data left to push, but still waiting for rx data,
		 * enable receive data available interrupt.
		 */
		spi_imx->intctrl(spi_imx, MXC_INT_RR);
		return IRQ_HANDLED;
	}

	spi_imx->intctrl(spi_imx, 0);
	complete(&spi_imx->xfer_done);

	return IRQ_HANDLED;
}