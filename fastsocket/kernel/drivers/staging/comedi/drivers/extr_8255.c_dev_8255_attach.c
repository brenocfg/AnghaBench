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
struct comedi_device {char* board_name; int n_subdevices; TYPE_1__* subdevices; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int COMEDI_NDEVCONFOPTS ; 
 int /*<<< orphan*/  COMEDI_SUBD_UNUSED ; 
 int EINVAL ; 
 int /*<<< orphan*/  _8255_SIZE ; 
 int alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  subdev_8255_init (struct comedi_device*,TYPE_1__*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dev_8255_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	int ret;
	unsigned long iobase;
	int i;

	printk("comedi%d: 8255:", dev->minor);

	dev->board_name = "8255";

	for (i = 0; i < COMEDI_NDEVCONFOPTS; i++) {
		iobase = it->options[i];
		if (!iobase)
			break;
	}
	if (i == 0) {
		printk(" no devices specified\n");
		return -EINVAL;
	}

	ret = alloc_subdevices(dev, i);
	if (ret < 0)
		return ret;

	for (i = 0; i < dev->n_subdevices; i++) {
		iobase = it->options[i];

		printk(" 0x%04lx", iobase);
		if (!request_region(iobase, _8255_SIZE, "8255")) {
			printk(" (I/O port conflict)");

			dev->subdevices[i].type = COMEDI_SUBD_UNUSED;
		} else {
			subdev_8255_init(dev, dev->subdevices + i, NULL,
					 iobase);
		}
	}

	printk("\n");

	return 0;
}