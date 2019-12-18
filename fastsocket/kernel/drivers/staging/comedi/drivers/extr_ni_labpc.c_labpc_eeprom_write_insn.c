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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int labpc_eeprom_write (struct comedi_device*,int,unsigned int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int labpc_eeprom_write_insn(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{
	int channel = CR_CHAN(insn->chanspec);
	int ret;

	/*  only allow writes to user area of eeprom */
	if (channel < 16 || channel > 127) {
		printk
		    ("eeprom writes are only allowed to channels 16 through 127 (the pointer and user areas)");
		return -EINVAL;
	}

	ret = labpc_eeprom_write(dev, channel, data[0]);
	if (ret < 0)
		return ret;

	return 1;
}