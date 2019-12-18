#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct spi_message {int /*<<< orphan*/  state; int /*<<< orphan*/  actual_length; } ;
struct driver_data {int /*<<< orphan*/  dma_channel; TYPE_1__* pdev; int /*<<< orphan*/  pump_transfers; scalar_t__ cs_change; scalar_t__ len_in_bytes; int /*<<< orphan*/ * tx; struct spi_message* cur_msg; struct chip_data* cur_chip; } ;
struct chip_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short DMA_ERR ; 
 int DMA_RUN ; 
 int /*<<< orphan*/  ERROR_STATE ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RBSY ; 
 int SPIF ; 
 int TXS ; 
 int /*<<< orphan*/  bfin_spi_cs_deactive (struct driver_data*,struct chip_data*) ; 
 int /*<<< orphan*/  bfin_spi_next_transfer (struct driver_data*) ; 
 int /*<<< orphan*/  clear_dma_irqstat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned short,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_disable_irq (int /*<<< orphan*/ ) ; 
 int get_dma_curr_irqstat (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int read_STAT (struct driver_data*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t bfin_spi_dma_irq_handler(int irq, void *dev_id)
{
	struct driver_data *drv_data = dev_id;
	struct chip_data *chip = drv_data->cur_chip;
	struct spi_message *msg = drv_data->cur_msg;
	unsigned long timeout;
	unsigned short dmastat = get_dma_curr_irqstat(drv_data->dma_channel);
	u16 spistat = read_STAT(drv_data);

	dev_dbg(&drv_data->pdev->dev,
		"in dma_irq_handler dmastat:0x%x spistat:0x%x\n",
		dmastat, spistat);

	clear_dma_irqstat(drv_data->dma_channel);

	/* Wait for DMA to complete */
	while (get_dma_curr_irqstat(drv_data->dma_channel) & DMA_RUN)
		cpu_relax();

	/*
	 * wait for the last transaction shifted out.  HRM states:
	 * at this point there may still be data in the SPI DMA FIFO waiting
	 * to be transmitted ... software needs to poll TXS in the SPI_STAT
	 * register until it goes low for 2 successive reads
	 */
	if (drv_data->tx != NULL) {
		while ((read_STAT(drv_data) & TXS) ||
		       (read_STAT(drv_data) & TXS))
			cpu_relax();
	}

	dev_dbg(&drv_data->pdev->dev,
		"in dma_irq_handler dmastat:0x%x spistat:0x%x\n",
		dmastat, read_STAT(drv_data));

	timeout = jiffies + HZ;
	while (!(read_STAT(drv_data) & SPIF))
		if (!time_before(jiffies, timeout)) {
			dev_warn(&drv_data->pdev->dev, "timeout waiting for SPIF");
			break;
		} else
			cpu_relax();

	if ((dmastat & DMA_ERR) && (spistat & RBSY)) {
		msg->state = ERROR_STATE;
		dev_err(&drv_data->pdev->dev, "dma receive: fifo/buffer overflow\n");
	} else {
		msg->actual_length += drv_data->len_in_bytes;

		if (drv_data->cs_change)
			bfin_spi_cs_deactive(drv_data, chip);

		/* Move to next transfer */
		msg->state = bfin_spi_next_transfer(drv_data);
	}

	/* Schedule transfer tasklet */
	tasklet_schedule(&drv_data->pump_transfers);

	/* free the irq handler before next transfer */
	dev_dbg(&drv_data->pdev->dev,
		"disable dma channel irq%d\n",
		drv_data->dma_channel);
	dma_disable_irq(drv_data->dma_channel);

	return IRQ_HANDLED;
}