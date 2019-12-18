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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/ * subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aio_aio12_8_detach(struct comedi_device *dev)
{
	subdev_8255_cleanup(dev, &dev->subdevices[2]);
	if (dev->iobase)
		release_region(dev->iobase, 24);
	return 0;
}