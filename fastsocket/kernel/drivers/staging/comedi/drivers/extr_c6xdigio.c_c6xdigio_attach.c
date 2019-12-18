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
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  type; int /*<<< orphan*/  insn_write; } ;
struct comedi_device {unsigned long iobase; char* board_name; struct comedi_subdevice* subdevices; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  C6XDIGIO_SIZE ; 
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int /*<<< orphan*/  COMEDI_SUBD_COUNTER ; 
 int EIO ; 
 int SDF_LSAMPL ; 
 int SDF_READABLE ; 
 int SDF_WRITEABLE ; 
 int alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  board_init (struct comedi_device*) ; 
 int /*<<< orphan*/  c6xdigio_ei_insn_read ; 
 int /*<<< orphan*/  c6xdigio_pnp_driver ; 
 int /*<<< orphan*/  c6xdigio_pwmo_insn_read ; 
 int /*<<< orphan*/  c6xdigio_pwmo_insn_write ; 
 int /*<<< orphan*/  pnp_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_unknown ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int c6xdigio_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	int result = 0;
	unsigned long iobase;
	unsigned int irq;
	struct comedi_subdevice *s;

	iobase = it->options[0];
	printk("comedi%d: c6xdigio: 0x%04lx\n", dev->minor, iobase);
	if (!request_region(iobase, C6XDIGIO_SIZE, "c6xdigio")) {
		printk("comedi%d: I/O port conflict\n", dev->minor);
		return -EIO;
	}
	dev->iobase = iobase;
	dev->board_name = "c6xdigio";

	result = alloc_subdevices(dev, 2);	/*  3 with encoder_init write */
	if (result < 0)
		return result;

	/*  Make sure that PnP ports gets activated */
	pnp_register_driver(&c6xdigio_pnp_driver);

	irq = it->options[1];
	if (irq > 0) {
		printk("comedi%d: irq = %u ignored\n", dev->minor, irq);
	} else if (irq == 0) {
		printk("comedi%d: no irq\n", dev->minor);
	}

	s = dev->subdevices + 0;
	/* pwm output subdevice */
	s->type = COMEDI_SUBD_AO;	/*  Not sure what to put here */
	s->subdev_flags = SDF_WRITEABLE;
	s->n_chan = 2;
	/*      s->trig[0] = c6xdigio_pwmo; */
	s->insn_read = c6xdigio_pwmo_insn_read;
	s->insn_write = c6xdigio_pwmo_insn_write;
	s->maxdata = 500;
	s->range_table = &range_bipolar10;	/*  A suitable lie */

	s = dev->subdevices + 1;
	/* encoder (counter) subdevice */
	s->type = COMEDI_SUBD_COUNTER;
	s->subdev_flags = SDF_READABLE | SDF_LSAMPL;
	s->n_chan = 2;
	/* s->trig[0] = c6xdigio_ei; */
	s->insn_read = c6xdigio_ei_insn_read;
	s->maxdata = 0xffffff;
	s->range_table = &range_unknown;

	/*           s = dev->subdevices + 2; */
	/* pwm output subdevice */
	/*       s->type = COMEDI_SUBD_COUNTER;  // Not sure what to put here */
	/*       s->subdev_flags = SDF_WRITEABLE; */
	/*       s->n_chan = 1; */
	/*       s->trig[0] = c6xdigio_ei_init; */
	/*       s->insn_read = c6xdigio_ei_init_insn_read; */
	/*       s->insn_write = c6xdigio_ei_init_insn_write; */
	/*       s->maxdata = 0xFFFF;  // Really just a don't care */
	/*       s->range_table = &range_unknown; // Not sure what to put here */

	/*  I will call this init anyway but more than likely the DSP board will not be connect */
	/*  when device driver is loaded. */
	board_init(dev);

	return 0;
}