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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {TYPE_1__ cmd; } ;
struct TYPE_6__ {int* hwrange; } ;
struct TYPE_5__ {int ao_bits; } ;

/* Variables and functions */
 size_t CR_RANGE (int /*<<< orphan*/ ) ; 
 int PCI224_DACCON_POLAR_MASK ; 
 int PCI224_DACCON_POLAR_UNI ; 
 TYPE_3__* devpriv ; 
 TYPE_2__* thisboard ; 

__attribute__((used)) static void
pci224_ao_munge(struct comedi_device *dev, struct comedi_subdevice *s,
		void *data, unsigned int num_bytes, unsigned int chan_index)
{
	struct comedi_async *async = s->async;
	short *array = data;
	unsigned int length = num_bytes / sizeof(*array);
	unsigned int offset;
	unsigned int shift;
	unsigned int i;

	/* The hardware expects 16-bit numbers. */
	shift = 16 - thisboard->ao_bits;
	/* Channels will be all bipolar or all unipolar. */
	if ((devpriv->hwrange[CR_RANGE(async->cmd.chanlist[0])] &
	     PCI224_DACCON_POLAR_MASK) == PCI224_DACCON_POLAR_UNI) {
		/* Unipolar */
		offset = 0;
	} else {
		/* Bipolar */
		offset = 32768;
	}
	/* Munge the data. */
	for (i = 0; i < length; i++) {
		array[i] = (array[i] << shift) - offset;
	}
}