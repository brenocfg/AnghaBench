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
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int* trimpot_value; } ;
struct TYPE_3__ {int trimpot; } ;

/* Variables and functions */
#define  AD7376 129 
#define  AD8402 128 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 TYPE_1__* thisboard ; 
 int /*<<< orphan*/  trimpot_7376_write (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  trimpot_8402_write (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int cb_pcidas_trimpot_write(struct comedi_device *dev,
				   unsigned int channel, unsigned int value)
{
	if (devpriv->trimpot_value[channel] == value)
		return 1;

	devpriv->trimpot_value[channel] = value;
	switch (thisboard->trimpot) {
	case AD7376:
		trimpot_7376_write(dev, value);
		break;
	case AD8402:
		trimpot_8402_write(dev, channel, value);
		break;
	default:
		comedi_error(dev, "driver bug?");
		return -1;
		break;
	}

	return 1;
}