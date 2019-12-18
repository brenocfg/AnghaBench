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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
#define  APCI3XXX_CONFIGURATION 128 
 int i_APCI3XXX_AnalogInputConfigOperatingMode (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int i_APCI3XXX_InsnConfigAnalogInput(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 1) {
		switch ((unsigned char) data[0]) {
		case APCI3XXX_CONFIGURATION:
			i_ReturnValue =
				i_APCI3XXX_AnalogInputConfigOperatingMode(dev,
				s, insn, data);
			break;

		default:
			i_ReturnValue = -100;
			printk("Config command error %d\n", data[0]);
			break;
		}
	} else {
	   /*******************/
		/* Data size error */
	   /*******************/

		printk("Buffer size error\n");
		i_ReturnValue = -101;
	}

	return i_ReturnValue;
}