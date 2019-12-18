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
#define  APCI1710_INCCPT_COUNTERAUTOTEST 134 
#define  APCI1710_INCCPT_INITCOMPARELOGIC 133 
#define  APCI1710_INCCPT_INITCOUNTER 132 
#define  APCI1710_INCCPT_INITEXTERNALSTROBE 131 
#define  APCI1710_INCCPT_INITFREQUENCYMEASUREMENT 130 
#define  APCI1710_INCCPT_INITINDEX 129 
#define  APCI1710_INCCPT_INITREFERENCE 128 
 int /*<<< orphan*/  CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 int i_APCI1710_CounterAutoTest (struct comedi_device*,unsigned char*) ; 
 int i_APCI1710_InitCompareLogic (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int i_APCI1710_InitCounter (struct comedi_device*,int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int i_APCI1710_InitExternalStrobe (struct comedi_device*,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 int i_APCI1710_InitFrequencyMeasurement (struct comedi_device*,int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned int,unsigned int*) ; 
 int i_APCI1710_InitIndex (struct comedi_device*,int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int i_APCI1710_InitReference (struct comedi_device*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnConfigINCCPT(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_ConfigType;
	int i_ReturnValue = 0;
	ui_ConfigType = CR_CHAN(insn->chanspec);

	printk("\nINC_CPT");

	devpriv->tsk_Current = current;	/*  Save the current process task structure */
	switch (ui_ConfigType) {
	case APCI1710_INCCPT_INITCOUNTER:
		i_ReturnValue = i_APCI1710_InitCounter(dev,
			CR_AREF(insn->chanspec),
			(unsigned char) data[0],
			(unsigned char) data[1],
			(unsigned char) data[2], (unsigned char) data[3], (unsigned char) data[4]);
		break;

	case APCI1710_INCCPT_COUNTERAUTOTEST:
		i_ReturnValue = i_APCI1710_CounterAutoTest(dev,
			(unsigned char *) &data[0]);
		break;

	case APCI1710_INCCPT_INITINDEX:
		i_ReturnValue = i_APCI1710_InitIndex(dev,
			CR_AREF(insn->chanspec),
			(unsigned char) data[0],
			(unsigned char) data[1], (unsigned char) data[2], (unsigned char) data[3]);
		break;

	case APCI1710_INCCPT_INITREFERENCE:
		i_ReturnValue = i_APCI1710_InitReference(dev,
			CR_AREF(insn->chanspec), (unsigned char) data[0]);
		break;

	case APCI1710_INCCPT_INITEXTERNALSTROBE:
		i_ReturnValue = i_APCI1710_InitExternalStrobe(dev,
			CR_AREF(insn->chanspec),
			(unsigned char) data[0], (unsigned char) data[1]);
		break;

	case APCI1710_INCCPT_INITCOMPARELOGIC:
		i_ReturnValue = i_APCI1710_InitCompareLogic(dev,
			CR_AREF(insn->chanspec), (unsigned int) data[0]);
		break;

	case APCI1710_INCCPT_INITFREQUENCYMEASUREMENT:
		i_ReturnValue = i_APCI1710_InitFrequencyMeasurement(dev,
			CR_AREF(insn->chanspec),
			(unsigned char) data[0],
			(unsigned char) data[1], (unsigned int) data[2], (unsigned int *) &data[0]);
		break;

	default:
		printk("Insn Config : Config Parameter Wrong\n");

	}

	if (i_ReturnValue >= 0)
		i_ReturnValue = insn->n;
	return i_ReturnValue;
}