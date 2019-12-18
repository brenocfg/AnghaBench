#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int subsystem_vendor; scalar_t__ subsystem_device; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct daqboard2000_private {int dummy; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned long iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; TYPE_4__* board_ptr; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int* options; } ;
struct TYPE_8__ {int id; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int got_regions; void* daq; void* plx; struct pci_dev* pci_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */
 size_t COMEDI_DEVCONF_AUX_DATA_LENGTH ; 
 int /*<<< orphan*/  COMEDI_SUBD_AI ; 
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int /*<<< orphan*/  DAQBOARD2000_DAQ_SIZE ; 
 int /*<<< orphan*/  DAQBOARD2000_PLX_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int SDF_GROUND ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int alloc_private (struct comedi_device*,int) ; 
 int alloc_subdevices (struct comedi_device*,int) ; 
 TYPE_4__* boardtypes ; 
 void* comedi_aux_data (int*,int /*<<< orphan*/ ) ; 
 int comedi_pci_enable (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  daqboard2000_8255_cb ; 
 int /*<<< orphan*/  daqboard2000_ai_insn_read ; 
 int /*<<< orphan*/  daqboard2000_ao_insn_read ; 
 int /*<<< orphan*/  daqboard2000_ao_insn_write ; 
 int /*<<< orphan*/  daqboard2000_initializeAdc (struct comedi_device*) ; 
 int /*<<< orphan*/  daqboard2000_initializeDac (struct comedi_device*) ; 
 TYPE_3__* devpriv ; 
 int initialize_daqboard2000 (struct comedi_device*,void*,unsigned int) ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int n_boardtypes ; 
 struct pci_dev* pci_get_device (int,int,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_daqboard2000_ai ; 
 int /*<<< orphan*/  range_daqboard2000_ao ; 
 int /*<<< orphan*/  readl (void*) ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_2__* this_board ; 

__attribute__((used)) static int daqboard2000_attach(struct comedi_device *dev,
			       struct comedi_devconfig *it)
{
	int result = 0;
	struct comedi_subdevice *s;
	struct pci_dev *card = NULL;
	void *aux_data;
	unsigned int aux_len;
	int bus, slot;

	printk("comedi%d: daqboard2000:", dev->minor);

	bus = it->options[0];
	slot = it->options[1];

	result = alloc_private(dev, sizeof(struct daqboard2000_private));
	if (result < 0) {
		return -ENOMEM;
	}
	for (card = pci_get_device(0x1616, 0x0409, NULL);
	     card != NULL; card = pci_get_device(0x1616, 0x0409, card)) {
		if (bus || slot) {
			/* requested particular bus/slot */
			if (card->bus->number != bus ||
			    PCI_SLOT(card->devfn) != slot) {
				continue;
			}
		}
		break;		/* found one */
	}
	if (!card) {
		if (bus || slot)
			printk(" no daqboard2000 found at bus/slot: %d/%d\n",
			       bus, slot);
		else
			printk(" no daqboard2000 found\n");
		return -EIO;
	} else {
		u32 id;
		int i;
		devpriv->pci_dev = card;
		id = ((u32) card->
		      subsystem_device << 16) | card->subsystem_vendor;
		for (i = 0; i < n_boardtypes; i++) {
			if (boardtypes[i].id == id) {
				printk(" %s", boardtypes[i].name);
				dev->board_ptr = boardtypes + i;
			}
		}
		if (!dev->board_ptr) {
			printk
			    (" unknown subsystem id %08x (pretend it is an ids2)",
			     id);
			dev->board_ptr = boardtypes;
		}
	}

	result = comedi_pci_enable(card, "daqboard2000");
	if (result < 0) {
		printk(" failed to enable PCI device and request regions\n");
		return -EIO;
	}
	devpriv->got_regions = 1;
	devpriv->plx =
	    ioremap(pci_resource_start(card, 0), DAQBOARD2000_PLX_SIZE);
	devpriv->daq =
	    ioremap(pci_resource_start(card, 2), DAQBOARD2000_DAQ_SIZE);
	if (!devpriv->plx || !devpriv->daq) {
		return -ENOMEM;
	}

	result = alloc_subdevices(dev, 3);
	if (result < 0)
		goto out;

	readl(devpriv->plx + 0x6c);

	/*
	   u8 interrupt;
	   Windows code does restore interrupts, but since we don't use them...
	   pci_read_config_byte(card, PCI_INTERRUPT_LINE, &interrupt);
	   printk("Interrupt before is: %x\n", interrupt);
	 */

	aux_data = comedi_aux_data(it->options, 0);
	aux_len = it->options[COMEDI_DEVCONF_AUX_DATA_LENGTH];

	if (aux_data && aux_len) {
		result = initialize_daqboard2000(dev, aux_data, aux_len);
	} else {
		printk("no FPGA initialization code, aborting\n");
		result = -EIO;
	}
	if (result < 0)
		goto out;
	daqboard2000_initializeAdc(dev);
	daqboard2000_initializeDac(dev);
	/*
	   Windows code does restore interrupts, but since we don't use them...
	   pci_read_config_byte(card, PCI_INTERRUPT_LINE, &interrupt);
	   printk("Interrupt after is: %x\n", interrupt);
	 */

	dev->iobase = (unsigned long)devpriv->daq;

	dev->board_name = this_board->name;

	s = dev->subdevices + 0;
	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND;
	s->n_chan = 24;
	s->maxdata = 0xffff;
	s->insn_read = daqboard2000_ai_insn_read;
	s->range_table = &range_daqboard2000_ai;

	s = dev->subdevices + 1;
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 2;
	s->maxdata = 0xffff;
	s->insn_read = daqboard2000_ao_insn_read;
	s->insn_write = daqboard2000_ao_insn_write;
	s->range_table = &range_daqboard2000_ao;

	s = dev->subdevices + 2;
	result = subdev_8255_init(dev, s, daqboard2000_8255_cb,
				  (unsigned long)(dev->iobase + 0x40));

	printk("\n");
out:
	return result;
}