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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; scalar_t__* unused; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_5__ {size_t ui_Read; TYPE_1__* s_FIFOInterruptParameters; } ;
struct TYPE_6__ {TYPE_2__ s_InterruptParameters; } ;
struct TYPE_4__ {unsigned int b_OldModuleMask; unsigned int ul_OldInterruptMask; unsigned int ul_OldCounterLatchValue; } ;

/* Variables and functions */
#define  APCI1710_CHRONO_CONVERTVALUE 131 
#define  APCI1710_CHRONO_PROGRESS_STATUS 130 
#define  APCI1710_CHRONO_READINTERRUPT 129 
#define  APCI1710_CHRONO_READVALUE 128 
 int APCI1710_SAVE_INTERRUPT ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned char CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_3__* devpriv ; 
 int i_APCI1710_ConvertChronoValue (struct comedi_device*,unsigned char,unsigned int,unsigned int*,unsigned char*,unsigned char*,unsigned int*,unsigned int*,unsigned int*) ; 
 int i_APCI1710_GetChronoProgressStatus (struct comedi_device*,unsigned char,unsigned char*) ; 
 int i_APCI1710_ReadChronoValue (struct comedi_device*,unsigned char,unsigned int,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnReadChrono(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned char b_ReadType;
	int i_ReturnValue = insn->n;

	b_ReadType = CR_CHAN(insn->chanspec);

	switch (b_ReadType) {
	case APCI1710_CHRONO_PROGRESS_STATUS:
		i_ReturnValue = i_APCI1710_GetChronoProgressStatus(dev,
			(unsigned char) CR_AREF(insn->chanspec), (unsigned char *) &data[0]);
		break;

	case APCI1710_CHRONO_READVALUE:
		i_ReturnValue = i_APCI1710_ReadChronoValue(dev,
			(unsigned char) CR_AREF(insn->chanspec),
			(unsigned int) insn->unused[0],
			(unsigned char *) &data[0], (unsigned int *) &data[1]);
		break;

	case APCI1710_CHRONO_CONVERTVALUE:
		i_ReturnValue = i_APCI1710_ConvertChronoValue(dev,
			(unsigned char) CR_AREF(insn->chanspec),
			(unsigned int) insn->unused[0],
			(unsigned int *) &data[0],
			(unsigned char *) &data[1],
			(unsigned char *) &data[2],
			(unsigned int *) &data[3],
			(unsigned int *) &data[4], (unsigned int *) &data[5]);
		break;

	case APCI1710_CHRONO_READINTERRUPT:
		printk("In Chrono Read Interrupt\n");

		data[0] = devpriv->s_InterruptParameters.
			s_FIFOInterruptParameters[devpriv->
			s_InterruptParameters.ui_Read].b_OldModuleMask;
		data[1] = devpriv->s_InterruptParameters.
			s_FIFOInterruptParameters[devpriv->
			s_InterruptParameters.ui_Read].ul_OldInterruptMask;
		data[2] = devpriv->s_InterruptParameters.
			s_FIFOInterruptParameters[devpriv->
			s_InterruptParameters.ui_Read].ul_OldCounterLatchValue;

			     /**************************/
		/* Increment the read FIFO */
			     /***************************/

		devpriv->
			s_InterruptParameters.
			ui_Read = (devpriv->
			s_InterruptParameters.
			ui_Read + 1) % APCI1710_SAVE_INTERRUPT;
		break;

	default:
		printk("ReadType Parameter wrong\n");
	}

	if (i_ReturnValue >= 0)
		i_ReturnValue = insn->n;
	return i_ReturnValue;

}