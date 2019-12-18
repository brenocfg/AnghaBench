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
struct comedi_subdevice {struct comedi_subdevice* async; } ;
struct comedi_device {int n_subdevices; int /*<<< orphan*/ * close; int /*<<< orphan*/ * open; int /*<<< orphan*/ * write_subdev; int /*<<< orphan*/ * read_subdev; scalar_t__ irq; scalar_t__ iobase; int /*<<< orphan*/ * board_ptr; int /*<<< orphan*/ * board_name; scalar_t__ driver; struct comedi_subdevice* private; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_alloc (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_free_subdevice_minor (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  comedi_set_hw_dev (struct comedi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct comedi_subdevice*) ; 

__attribute__((used)) static void cleanup_device(struct comedi_device *dev)
{
	int i;
	struct comedi_subdevice *s;

	if (dev->subdevices) {
		for (i = 0; i < dev->n_subdevices; i++) {
			s = dev->subdevices + i;
			comedi_free_subdevice_minor(s);
			if (s->async) {
				comedi_buf_alloc(dev, s, 0);
				kfree(s->async);
			}
		}
		kfree(dev->subdevices);
		dev->subdevices = NULL;
		dev->n_subdevices = 0;
	}
	kfree(dev->private);
	dev->private = NULL;
	dev->driver = 0;
	dev->board_name = NULL;
	dev->board_ptr = NULL;
	dev->iobase = 0;
	dev->irq = 0;
	dev->read_subdev = NULL;
	dev->write_subdev = NULL;
	dev->open = NULL;
	dev->close = NULL;
	comedi_set_hw_dev(dev, NULL);
}