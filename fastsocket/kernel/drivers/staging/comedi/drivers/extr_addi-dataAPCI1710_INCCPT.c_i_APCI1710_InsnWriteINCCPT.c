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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
#define  APCI1710_INCCPT_DISABLECOMPARELOGIC 137 
#define  APCI1710_INCCPT_DISABLEFREQUENCYMEASUREMENT 136 
#define  APCI1710_INCCPT_DISABLEINDEX 135 
#define  APCI1710_INCCPT_DISABLELATCHINTERRUPT 134 
#define  APCI1710_INCCPT_ENABLECOMPARELOGIC 133 
#define  APCI1710_INCCPT_ENABLEFREQUENCYMEASUREMENT 132 
#define  APCI1710_INCCPT_ENABLEINDEX 131 
#define  APCI1710_INCCPT_ENABLELATCHINTERRUPT 130 
#define  APCI1710_INCCPT_WRITE16BITCOUNTERVALUE 129 
#define  APCI1710_INCCPT_WRITE32BITCOUNTERVALUE 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 int i_APCI1710_DisableCompareLogic (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_DisableFrequencyMeasurement (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_DisableIndex (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_DisableLatchInterrupt (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_EnableCompareLogic (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_EnableFrequencyMeasurement (struct comedi_device*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  i_APCI1710_EnableIndex (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_EnableLatchInterrupt (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_Write16BitCounterValue (struct comedi_device*,unsigned char,unsigned char,unsigned int) ; 
 int i_APCI1710_Write32BitCounterValue (struct comedi_device*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnWriteINCCPT(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_WriteType;
	int i_ReturnValue = 0;

	ui_WriteType = CR_CHAN(insn->chanspec);
	devpriv->tsk_Current = current;	/*  Save the current process task structure */

	switch (ui_WriteType) {
	case APCI1710_INCCPT_ENABLELATCHINTERRUPT:
		i_ReturnValue = i_APCI1710_EnableLatchInterrupt(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_DISABLELATCHINTERRUPT:
		i_ReturnValue = i_APCI1710_DisableLatchInterrupt(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_WRITE16BITCOUNTERVALUE:
		i_ReturnValue = i_APCI1710_Write16BitCounterValue(dev,
			(unsigned char) CR_AREF(insn->chanspec),
			(unsigned char) data[0], (unsigned int) data[1]);
		break;

	case APCI1710_INCCPT_WRITE32BITCOUNTERVALUE:
		i_ReturnValue = i_APCI1710_Write32BitCounterValue(dev,
			(unsigned char) CR_AREF(insn->chanspec), (unsigned int) data[0]);

		break;

	case APCI1710_INCCPT_ENABLEINDEX:
		i_APCI1710_EnableIndex(dev, (unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_DISABLEINDEX:
		i_ReturnValue = i_APCI1710_DisableIndex(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_ENABLECOMPARELOGIC:
		i_ReturnValue = i_APCI1710_EnableCompareLogic(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_DISABLECOMPARELOGIC:
		i_ReturnValue = i_APCI1710_DisableCompareLogic(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_ENABLEFREQUENCYMEASUREMENT:
		i_ReturnValue = i_APCI1710_EnableFrequencyMeasurement(dev,
			(unsigned char) CR_AREF(insn->chanspec), (unsigned char) data[0]);
		break;

	case APCI1710_INCCPT_DISABLEFREQUENCYMEASUREMENT:
		i_ReturnValue = i_APCI1710_DisableFrequencyMeasurement(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	default:
		printk("Write Config Parameter Wrong\n");
	}

	if (i_ReturnValue >= 0)
		i_ReturnValue = insn->n;
	return i_ReturnValue;
}