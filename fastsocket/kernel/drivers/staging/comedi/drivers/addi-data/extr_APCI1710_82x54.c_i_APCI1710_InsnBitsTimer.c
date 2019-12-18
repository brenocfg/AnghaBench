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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
#define  APCI1710_TIMER_GETOUTPUTLEVEL 131 
#define  APCI1710_TIMER_GETPROGRESSSTATUS 130 
#define  APCI1710_TIMER_READVALUE 129 
#define  APCI1710_TIMER_WRITEVALUE 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 int i_APCI1710_GetTimerOutputLevel (struct comedi_device*,unsigned char,unsigned char,unsigned char*) ; 
 int i_APCI1710_GetTimerProgressStatus (struct comedi_device*,unsigned char,unsigned char,unsigned char*) ; 
 int i_APCI1710_ReadTimerValue (struct comedi_device*,unsigned char,unsigned char,unsigned int*) ; 
 int i_APCI1710_WriteTimerValue (struct comedi_device*,unsigned char,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnBitsTimer(struct comedi_device *dev, struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	unsigned char b_BitsType;
	int i_ReturnValue = 0;
	b_BitsType = data[0];

	printk("\n82X54");

	switch (b_BitsType) {
	case APCI1710_TIMER_READVALUE:
		i_ReturnValue = i_APCI1710_ReadTimerValue(dev,
							  (unsigned char)CR_AREF(insn->chanspec),
							  (unsigned char)CR_CHAN(insn->chanspec),
							  (unsigned int *) &data[0]);
		break;

	case APCI1710_TIMER_GETOUTPUTLEVEL:
		i_ReturnValue = i_APCI1710_GetTimerOutputLevel(dev,
							       (unsigned char)CR_AREF(insn->chanspec),
							       (unsigned char)CR_CHAN(insn->chanspec),
							       (unsigned char *) &data[0]);
		break;

	case APCI1710_TIMER_GETPROGRESSSTATUS:
		i_ReturnValue = i_APCI1710_GetTimerProgressStatus(dev,
								  (unsigned char)CR_AREF(insn->chanspec),
								  (unsigned char)CR_CHAN(insn->chanspec),
								  (unsigned char *)&data[0]);
		break;

	case APCI1710_TIMER_WRITEVALUE:
		i_ReturnValue = i_APCI1710_WriteTimerValue(dev,
							   (unsigned char)CR_AREF(insn->chanspec),
							   (unsigned char)CR_CHAN(insn->chanspec),
							   (unsigned int)data[1]);

		break;

	default:
		printk("Bits Config Parameter Wrong\n");
		i_ReturnValue = -1;
	}

	if (i_ReturnValue >= 0)
		i_ReturnValue = insn->n;
	return i_ReturnValue;
}