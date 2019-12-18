#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ subdevices; scalar_t__ private; } ;
struct TYPE_4__ {scalar_t__ has_8255; } ;
struct TYPE_3__ {scalar_t__ counter_dev; } ;

/* Variables and functions */
 scalar_t__ NI_8255_DIO_SUBDEV ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_gpct_device_destroy (scalar_t__) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 

__attribute__((used)) static void mio_common_detach(struct comedi_device *dev)
{
	if (dev->private) {
		if (devpriv->counter_dev) {
			ni_gpct_device_destroy(devpriv->counter_dev);
		}
	}
	if (dev->subdevices && boardtype.has_8255)
		subdev_8255_cleanup(dev, dev->subdevices + NI_8255_DIO_SUBDEV);
}