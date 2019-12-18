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
typedef  int u64 ;
struct comedi_subdevice {int maxdata; TYPE_1__* range_table; } ;
struct comedi_krange {unsigned long max; unsigned long min; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; } ;
struct TYPE_4__ {int uvolt_amplitude; unsigned long usec_period; } ;
struct TYPE_3__ {struct comedi_krange* range; } ;

/* Variables and functions */
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 

__attribute__((used)) static short fake_sawtooth(struct comedi_device *dev, unsigned int range_index,
			   unsigned long current_time)
{
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int offset = s->maxdata / 2;
	u64 value;
	const struct comedi_krange *krange =
	    &s->range_table->range[range_index];
	u64 binary_amplitude;

	binary_amplitude = s->maxdata;
	binary_amplitude *= devpriv->uvolt_amplitude;
	do_div(binary_amplitude, krange->max - krange->min);

	current_time %= devpriv->usec_period;
	value = current_time;
	value *= binary_amplitude * 2;
	do_div(value, devpriv->usec_period);
	value -= binary_amplitude;	/* get rid of sawtooth's dc offset */

	return offset + value;
}