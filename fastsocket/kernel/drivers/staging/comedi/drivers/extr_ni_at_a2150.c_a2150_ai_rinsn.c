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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {unsigned int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int config_bits; int irq_dma_bits; } ;

/* Variables and functions */
 int AC0_BIT ; 
 int AC1_BIT ; 
 scalar_t__ CONFIG_REG ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int DMA_EN_BIT ; 
 int DMA_INTR_EN_BIT ; 
 int ETIME ; 
 scalar_t__ FIFO_DATA_REG ; 
 scalar_t__ FIFO_RESET_REG ; 
 scalar_t__ FIFO_START_REG ; 
 int FNE_BIT ; 
 scalar_t__ IRQ_DMA_CNTRL_REG ; 
 scalar_t__ STATUS_REG ; 
 scalar_t__ TRIGGER_REG ; 
 scalar_t__ a2150_set_chanlist (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  ni_dump_regs (struct comedi_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int a2150_ai_rinsn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	unsigned int i, n;
	static const int timeout = 100000;
	static const int filter_delay = 36;

	/*  clear fifo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	/* setup chanlist */
	if (a2150_set_chanlist(dev, CR_CHAN(insn->chanspec), 1) < 0)
		return -1;

	/*  set dc coupling */
	devpriv->config_bits &= ~AC0_BIT;
	devpriv->config_bits &= ~AC1_BIT;

	/*  send timing, channel, config bits */
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);

	/*  disable dma on card */
	devpriv->irq_dma_bits &= ~DMA_INTR_EN_BIT & ~DMA_EN_BIT;
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/*  setup start triggering */
	outw(0, dev->iobase + TRIGGER_REG);

	/*  start aquisition for soft trigger */
	outw(0, dev->iobase + FIFO_START_REG);

	/* there is a 35.6 sample delay for data to get through the antialias filter */
	for (n = 0; n < filter_delay; n++) {
		for (i = 0; i < timeout; i++) {
			if (inw(dev->iobase + STATUS_REG) & FNE_BIT)
				break;
			udelay(1);
		}
		if (i == timeout) {
			comedi_error(dev, "timeout");
			return -ETIME;
		}
		inw(dev->iobase + FIFO_DATA_REG);
	}

	/*  read data */
	for (n = 0; n < insn->n; n++) {
		for (i = 0; i < timeout; i++) {
			if (inw(dev->iobase + STATUS_REG) & FNE_BIT)
				break;
			udelay(1);
		}
		if (i == timeout) {
			comedi_error(dev, "timeout");
			return -ETIME;
		}
#ifdef A2150_DEBUG
		ni_dump_regs(dev);
#endif
		data[n] = inw(dev->iobase + FIFO_DATA_REG);
#ifdef A2150_DEBUG
		printk(" data is %i\n", data[n]);
#endif
		data[n] ^= 0x8000;
	}

	/*  clear fifo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	return n;
}