#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  ui_Address; } ;
struct TYPE_10__ {TYPE_4__ s_BoardInfos; TYPE_3__* s_ModuleInfo; } ;
struct TYPE_7__ {unsigned int dw_StatusRegister; TYPE_1__* s_PulseEncoderInfo; } ;
struct TYPE_8__ {TYPE_2__ s_PulseEncoderModuleInfo; } ;
struct TYPE_6__ {int b_PulseEncoderInit; } ;

/* Variables and functions */
#define  APCI1710_PULSEENCODER_READ 129 
#define  APCI1710_PULSEENCODER_WRITE 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

int i_APCI1710_InsnBitsReadWritePulseEncoder(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_StatusRegister;
	unsigned char b_ModulNbr;
	unsigned char b_PulseEncoderNbr;
	unsigned char *pb_Status;
	unsigned char b_Type;
	unsigned int *pul_ReadValue;
	unsigned int ul_WriteValue;

	i_ReturnValue = insn->n;
	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_Type = (unsigned char) data[0];
	b_PulseEncoderNbr = (unsigned char) data[1];
	pb_Status = (unsigned char *) &data[0];
	pul_ReadValue = (unsigned int *) &data[1];

	/***********************************/
	/* Test the selected module number */
	/***********************************/

	if (b_ModulNbr <= 3) {
	   /******************************************/
		/* Test the selected pulse encoder number */
	   /******************************************/

		if (b_PulseEncoderNbr <= 3) {
	      /*************************************/
			/* Test if pulse encoder initialised */
	      /*************************************/

			if (devpriv->s_ModuleInfo[b_ModulNbr].
				s_PulseEncoderModuleInfo.
				s_PulseEncoderInfo[b_PulseEncoderNbr].
				b_PulseEncoderInit == 1) {

				switch (b_Type) {
				case APCI1710_PULSEENCODER_READ:
		 /****************************/
					/* Read the status register */
		 /****************************/

					dw_StatusRegister =
						inl(devpriv->s_BoardInfos.
						ui_Address + 16 +
						(64 * b_ModulNbr));

					devpriv->s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_StatusRegister = devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_StatusRegister |
						dw_StatusRegister;

					*pb_Status =
						(unsigned char) (devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_StatusRegister >> (1 +
							b_PulseEncoderNbr)) & 1;

					devpriv->s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_StatusRegister =
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_PulseEncoderModuleInfo.
						dw_StatusRegister &
						(0xFFFFFFFFUL - (1 << (1 +
								b_PulseEncoderNbr)));

		 /******************/
					/* Read the value */
		 /******************/

					*pul_ReadValue =
						inl(devpriv->s_BoardInfos.
						ui_Address +
						(4 * b_PulseEncoderNbr) +
						(64 * b_ModulNbr));
					break;

				case APCI1710_PULSEENCODER_WRITE:
					ul_WriteValue = (unsigned int) data[2];
			/*******************/
					/* Write the value */
			/*******************/

					outl(ul_WriteValue,
						devpriv->s_BoardInfos.
						ui_Address +
						(4 * b_PulseEncoderNbr) +
						(64 * b_ModulNbr));

				}	/* end of switch */
			} else {
		 /*********************************/
				/* Pulse encoder not initialised */
		 /*********************************/

				DPRINTK("Pulse encoder not initialised\n");
				i_ReturnValue = -4;
			}
		} else {
	      /************************************/
			/* Pulse encoder selection is wrong */
	      /************************************/

			DPRINTK("Pulse encoder selection is wrong\n");
			i_ReturnValue = -3;
		}
	} else {
	   /*****************************/
		/* Module selection is wrong */
	   /*****************************/

		DPRINTK("Module selection is wrong\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}