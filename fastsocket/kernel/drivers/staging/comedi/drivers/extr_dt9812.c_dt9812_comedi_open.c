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
struct comedi_subdevice {int n_chan; int maxdata; int /*<<< orphan*/ * range_table; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct TYPE_6__ {TYPE_2__* slot; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_1__* usb; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt9812_10_ain_range ; 
 int /*<<< orphan*/  dt9812_10_aout_range ; 
 int /*<<< orphan*/  dt9812_2pt5_ain_range ; 
 int /*<<< orphan*/  dt9812_2pt5_aout_range ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dt9812_comedi_open(struct comedi_device *dev)
{
	down(&devpriv->slot->mutex);
	if (devpriv->slot->usb) {
		/* We have an attached device, fill in current range info */
		struct comedi_subdevice *s;

		s = &dev->subdevices[0];
		s->n_chan = 8;
		s->maxdata = 1;

		s = &dev->subdevices[1];
		s->n_chan = 8;
		s->maxdata = 1;

		s = &dev->subdevices[2];
		s->n_chan = 8;
		switch (devpriv->slot->usb->device) {
		case 0:{
				s->maxdata = 4095;
				s->range_table = &dt9812_10_ain_range;
			}
			break;
		case 1:{
				s->maxdata = 4095;
				s->range_table = &dt9812_2pt5_ain_range;
			}
			break;
		}

		s = &dev->subdevices[3];
		s->n_chan = 2;
		switch (devpriv->slot->usb->device) {
		case 0:{
				s->maxdata = 4095;
				s->range_table = &dt9812_10_aout_range;
			}
			break;
		case 1:{
				s->maxdata = 4095;
				s->range_table = &dt9812_2pt5_aout_range;
			}
			break;
		}
	}
	up(&devpriv->slot->mutex);
}