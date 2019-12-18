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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; } ;
struct comedi_async {int events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ dio_count; scalar_t__ plx9080_iobase; scalar_t__ hpdi_iobase; } ;

/* Variables and functions */
 scalar_t__ BOARD_STATUS_REG ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,...) ; 
 int ICS_DMA0_A ; 
 int ICS_DMA1_A ; 
 int ICS_LDIA ; 
 int ICS_LIA ; 
 scalar_t__ INTERRUPT_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PLX_CLEAR_DMA_INTR_BIT ; 
 scalar_t__ PLX_DBR_OUT_REG ; 
 scalar_t__ PLX_DMA0_CS_REG ; 
 scalar_t__ PLX_DMA1_CS_REG ; 
 int PLX_DMA_EN_BIT ; 
 scalar_t__ PLX_INTRCS_REG ; 
 int RX_OVERRUN_BIT ; 
 int RX_UNDERRUN_BIT ; 
 int /*<<< orphan*/  cfc_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  drain_dma_buffers (struct comedi_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t handle_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	uint32_t hpdi_intr_status, hpdi_board_status;
	uint32_t plx_status;
	uint32_t plx_bits;
	uint8_t dma0_status, dma1_status;
	unsigned long flags;

	if (!dev->attached) {
		return IRQ_NONE;
	}

	plx_status = readl(priv(dev)->plx9080_iobase + PLX_INTRCS_REG);
	if ((plx_status & (ICS_DMA0_A | ICS_DMA1_A | ICS_LIA)) == 0) {
		return IRQ_NONE;
	}

	hpdi_intr_status = readl(priv(dev)->hpdi_iobase + INTERRUPT_STATUS_REG);
	hpdi_board_status = readl(priv(dev)->hpdi_iobase + BOARD_STATUS_REG);

	async->events = 0;

	if (hpdi_intr_status) {
		DEBUG_PRINT("hpdi: intr status 0x%x, ", hpdi_intr_status);
		writel(hpdi_intr_status,
		       priv(dev)->hpdi_iobase + INTERRUPT_STATUS_REG);
	}
	/*  spin lock makes sure noone else changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma0_status = readb(priv(dev)->plx9080_iobase + PLX_DMA0_CS_REG);
	if (plx_status & ICS_DMA0_A) {	/*  dma chan 0 interrupt */
		writeb((dma0_status & PLX_DMA_EN_BIT) | PLX_CLEAR_DMA_INTR_BIT,
		       priv(dev)->plx9080_iobase + PLX_DMA0_CS_REG);

		DEBUG_PRINT("dma0 status 0x%x\n", dma0_status);
		if (dma0_status & PLX_DMA_EN_BIT) {
			drain_dma_buffers(dev, 0);
		}
		DEBUG_PRINT(" cleared dma ch0 interrupt\n");
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  spin lock makes sure noone else changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma1_status = readb(priv(dev)->plx9080_iobase + PLX_DMA1_CS_REG);
	if (plx_status & ICS_DMA1_A) {	/*  XXX *//*  dma chan 1 interrupt */
		writeb((dma1_status & PLX_DMA_EN_BIT) | PLX_CLEAR_DMA_INTR_BIT,
		       priv(dev)->plx9080_iobase + PLX_DMA1_CS_REG);
		DEBUG_PRINT("dma1 status 0x%x\n", dma1_status);

		DEBUG_PRINT(" cleared dma ch1 interrupt\n");
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  clear possible plx9080 interrupt sources */
	if (plx_status & ICS_LDIA) {	/*  clear local doorbell interrupt */
		plx_bits = readl(priv(dev)->plx9080_iobase + PLX_DBR_OUT_REG);
		writel(plx_bits, priv(dev)->plx9080_iobase + PLX_DBR_OUT_REG);
		DEBUG_PRINT(" cleared local doorbell bits 0x%x\n", plx_bits);
	}

	if (hpdi_board_status & RX_OVERRUN_BIT) {
		comedi_error(dev, "rx fifo overrun");
		async->events |= COMEDI_CB_EOA | COMEDI_CB_ERROR;
		DEBUG_PRINT("dma0_status 0x%x\n",
			    (int)readb(priv(dev)->plx9080_iobase +
				       PLX_DMA0_CS_REG));
	}

	if (hpdi_board_status & RX_UNDERRUN_BIT) {
		comedi_error(dev, "rx fifo underrun");
		async->events |= COMEDI_CB_EOA | COMEDI_CB_ERROR;
	}

	if (priv(dev)->dio_count == 0)
		async->events |= COMEDI_CB_EOA;

	DEBUG_PRINT("board status 0x%x, ", hpdi_board_status);
	DEBUG_PRINT("plx status 0x%x\n", plx_status);
	if (async->events)
		DEBUG_PRINT(" events 0x%x\n", async->events);

	cfc_handle_events(dev, s);

	return IRQ_HANDLED;
}