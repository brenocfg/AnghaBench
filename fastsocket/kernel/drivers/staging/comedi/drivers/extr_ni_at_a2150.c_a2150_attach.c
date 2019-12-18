#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int subdev_flags; int n_chan; int len_chanlist; int maxdata; int /*<<< orphan*/  cancel; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  do_cmdtest; int /*<<< orphan*/  do_cmd; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned long iobase; unsigned int irq; struct comedi_subdevice* read_subdev; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; scalar_t__ board_ptr; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct a2150_private {int dummy; } ;
struct TYPE_6__ {int irq_dma_bits; unsigned int dma; int config_bits; int /*<<< orphan*/ * dma_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2150_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  A2150_SIZE ; 
 int APD_BIT ; 
 int /*<<< orphan*/  COMEDI_SUBD_AI ; 
 scalar_t__ CONFIG_REG ; 
 int DCAL_BIT ; 
 int DMA_CHAN_BITS (unsigned int) ; 
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int DPD_BIT ; 
 int EINVAL ; 
 int EIO ; 
 int ENABLE0_BIT ; 
 int ENABLE1_BIT ; 
 int ENOMEM ; 
 int ETIME ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int HW_COUNT_DISABLE ; 
 scalar_t__ I8253_MODE_REG ; 
 scalar_t__ IRQ_DMA_CNTRL_REG ; 
 int IRQ_LVL_BITS (unsigned int) ; 
 int SDF_CMD_READ ; 
 int SDF_GROUND ; 
 int SDF_OTHER ; 
 int SDF_READABLE ; 
 scalar_t__ STATUS_REG ; 
 int /*<<< orphan*/  a2150_ai_cmd ; 
 int /*<<< orphan*/  a2150_ai_cmdtest ; 
 int /*<<< orphan*/  a2150_ai_rinsn ; 
 scalar_t__ a2150_boards ; 
 int /*<<< orphan*/  a2150_cancel ; 
 int /*<<< orphan*/  a2150_interrupt ; 
 scalar_t__ a2150_probe (struct comedi_device*) ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  disable_dma (unsigned int) ; 
 TYPE_2__ driver_a2150 ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  outw_p (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_a2150 ; 
 scalar_t__ request_dma (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_mode (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* thisboard ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int a2150_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	unsigned long iobase = it->options[0];
	unsigned int irq = it->options[1];
	unsigned int dma = it->options[2];
	static const int timeout = 2000;
	int i;

	printk("comedi%d: %s: io 0x%lx", dev->minor, driver_a2150.driver_name,
	       iobase);
	if (irq) {
		printk(", irq %u", irq);
	} else {
		printk(", no irq");
	}
	if (dma) {
		printk(", dma %u", dma);
	} else {
		printk(", no dma");
	}
	printk("\n");

	/* allocate and initialize dev->private */
	if (alloc_private(dev, sizeof(struct a2150_private)) < 0)
		return -ENOMEM;

	if (iobase == 0) {
		printk(" io base address required\n");
		return -EINVAL;
	}

	/* check if io addresses are available */
	if (!request_region(iobase, A2150_SIZE, driver_a2150.driver_name)) {
		printk(" I/O port conflict\n");
		return -EIO;
	}
	dev->iobase = iobase;

	/* grab our IRQ */
	if (irq) {
		/*  check that irq is supported */
		if (irq < 3 || irq == 8 || irq == 13 || irq > 15) {
			printk(" invalid irq line %u\n", irq);
			return -EINVAL;
		}
		if (request_irq(irq, a2150_interrupt, 0,
				driver_a2150.driver_name, dev)) {
			printk("unable to allocate irq %u\n", irq);
			return -EINVAL;
		}
		devpriv->irq_dma_bits |= IRQ_LVL_BITS(irq);
		dev->irq = irq;
	}
	/*  initialize dma */
	if (dma) {
		if (dma == 4 || dma > 7) {
			printk(" invalid dma channel %u\n", dma);
			return -EINVAL;
		}
		if (request_dma(dma, driver_a2150.driver_name)) {
			printk(" failed to allocate dma channel %u\n", dma);
			return -EINVAL;
		}
		devpriv->dma = dma;
		devpriv->dma_buffer =
		    kmalloc(A2150_DMA_BUFFER_SIZE, GFP_KERNEL | GFP_DMA);
		if (devpriv->dma_buffer == NULL)
			return -ENOMEM;

		disable_dma(dma);
		set_dma_mode(dma, DMA_MODE_READ);

		devpriv->irq_dma_bits |= DMA_CHAN_BITS(dma);
	}

	dev->board_ptr = a2150_boards + a2150_probe(dev);
	dev->board_name = thisboard->name;

	if (alloc_subdevices(dev, 1) < 0)
		return -ENOMEM;

	/* analog input subdevice */
	s = dev->subdevices + 0;
	dev->read_subdev = s;
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND | SDF_OTHER | SDF_CMD_READ;
	s->n_chan = 4;
	s->len_chanlist = 4;
	s->maxdata = 0xffff;
	s->range_table = &range_a2150;
	s->do_cmd = a2150_ai_cmd;
	s->do_cmdtest = a2150_ai_cmdtest;
	s->insn_read = a2150_ai_rinsn;
	s->cancel = a2150_cancel;

	/* need to do this for software counting of completed conversions, to
	 * prevent hardware count from stopping aquisition */
	outw(HW_COUNT_DISABLE, dev->iobase + I8253_MODE_REG);

	/*  set card's irq and dma levels */
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/*  reset and sync adc clock circuitry */
	outw_p(DPD_BIT | APD_BIT, dev->iobase + CONFIG_REG);
	outw_p(DPD_BIT, dev->iobase + CONFIG_REG);
	/*  initialize configuration register */
	devpriv->config_bits = 0;
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);
	/*  wait until offset calibration is done, then enable analog inputs */
	for (i = 0; i < timeout; i++) {
		if ((DCAL_BIT & inw(dev->iobase + STATUS_REG)) == 0)
			break;
		udelay(1000);
	}
	if (i == timeout) {
		printk
		    (" timed out waiting for offset calibration to complete\n");
		return -ETIME;
	}
	devpriv->config_bits |= ENABLE0_BIT | ENABLE1_BIT;
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);

	return 0;
}