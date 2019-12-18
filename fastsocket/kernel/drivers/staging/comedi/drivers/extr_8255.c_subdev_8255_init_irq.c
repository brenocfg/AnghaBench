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
struct comedi_subdevice {int /*<<< orphan*/  cancel; int /*<<< orphan*/  do_cmd; int /*<<< orphan*/  do_cmdtest; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int have_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  subdev_8255_cancel ; 
 int /*<<< orphan*/  subdev_8255_cmd ; 
 int /*<<< orphan*/  subdev_8255_cmdtest ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int (*) (int,int,int,unsigned long),unsigned long) ; 
 TYPE_1__* subdevpriv ; 

int subdev_8255_init_irq(struct comedi_device *dev, struct comedi_subdevice *s,
			 int (*cb) (int, int, int, unsigned long),
			 unsigned long arg)
{
	int ret;

	ret = subdev_8255_init(dev, s, cb, arg);
	if (ret < 0)
		return ret;

	s->do_cmdtest = subdev_8255_cmdtest;
	s->do_cmd = subdev_8255_cmd;
	s->cancel = subdev_8255_cancel;

	subdevpriv->have_irq = 1;

	return 0;
}