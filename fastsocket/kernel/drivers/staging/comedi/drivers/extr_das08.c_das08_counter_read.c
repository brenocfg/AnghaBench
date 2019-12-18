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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i8254; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 unsigned int i8254_read_channel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int das08_counter_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	int chan = insn->chanspec;

	/* printk("Reading counter channel %d ",chan); */
	data[0] = i8254_read_channel(&devpriv->i8254, chan);
	/* printk("=> 0x%08X\n",data[0]); */

	return 1;
}