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
#define  APCI1710_INCCPT_CLEARALLCOUNTERVALUE 134 
#define  APCI1710_INCCPT_CLEARCOUNTERVALUE 133 
#define  APCI1710_INCCPT_LATCHCOUNTER 132 
#define  APCI1710_INCCPT_SETDIGITALCHLOFF 131 
#define  APCI1710_INCCPT_SETDIGITALCHLON 130 
#define  APCI1710_INCCPT_SETINDEXANDREFERENCESOURCE 129 
#define  APCI1710_INCCPT_SETINPUTFILTER 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 int i_APCI1710_ClearAllCounterValue (struct comedi_device*) ; 
 int i_APCI1710_ClearCounterValue (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_LatchCounter (struct comedi_device*,unsigned char,unsigned char) ; 
 int i_APCI1710_SetDigitalChlOff (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_SetDigitalChlOn (struct comedi_device*,unsigned char) ; 
 int i_APCI1710_SetIndexAndReferenceSource (struct comedi_device*,unsigned char,unsigned char) ; 
 int i_APCI1710_SetInputFilter (struct comedi_device*,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnBitsINCCPT(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_BitsType;
	int i_ReturnValue = 0;
	ui_BitsType = CR_CHAN(insn->chanspec);
	devpriv->tsk_Current = current;	/*  Save the current process task structure */

	switch (ui_BitsType) {
	case APCI1710_INCCPT_CLEARCOUNTERVALUE:
		i_ReturnValue = i_APCI1710_ClearCounterValue(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_CLEARALLCOUNTERVALUE:
		i_ReturnValue = i_APCI1710_ClearAllCounterValue(dev);
		break;

	case APCI1710_INCCPT_SETINPUTFILTER:
		i_ReturnValue = i_APCI1710_SetInputFilter(dev,
			(unsigned char) CR_AREF(insn->chanspec),
			(unsigned char) data[0], (unsigned char) data[1]);
		break;

	case APCI1710_INCCPT_LATCHCOUNTER:
		i_ReturnValue = i_APCI1710_LatchCounter(dev,
			(unsigned char) CR_AREF(insn->chanspec), (unsigned char) data[0]);
		break;

	case APCI1710_INCCPT_SETINDEXANDREFERENCESOURCE:
		i_ReturnValue = i_APCI1710_SetIndexAndReferenceSource(dev,
			(unsigned char) CR_AREF(insn->chanspec), (unsigned char) data[0]);
		break;

	case APCI1710_INCCPT_SETDIGITALCHLON:
		i_ReturnValue = i_APCI1710_SetDigitalChlOn(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	case APCI1710_INCCPT_SETDIGITALCHLOFF:
		i_ReturnValue = i_APCI1710_SetDigitalChlOff(dev,
			(unsigned char) CR_AREF(insn->chanspec));
		break;

	default:
		printk("Bits Config Parameter Wrong\n");
	}

	if (i_ReturnValue >= 0)
		i_ReturnValue = insn->n;
	return i_ReturnValue;
}