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
struct comedi_device {unsigned int n_subdevices; TYPE_1__* subdevices; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int ENODEV ; 

int comedi_find_subdevice_by_type(void *d, int type, unsigned int subd)
{
	struct comedi_device *dev = (struct comedi_device *)d;

	if (subd > dev->n_subdevices)
		return -ENODEV;

	for (; subd < dev->n_subdevices; subd++) {
		if (dev->subdevices[subd].type == type)
			return subd;
	}
	return -1;
}