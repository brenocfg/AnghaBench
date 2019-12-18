#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_7__ {int* dw_MolduleConfiguration; int /*<<< orphan*/  ui_Address; } ;
struct TYPE_8__ {TYPE_3__ s_BoardInfos; TYPE_2__* s_ModuleInfo; } ;
struct TYPE_5__ {int b_ChronoInit; } ;
struct TYPE_6__ {TYPE_1__ s_ChronoModuleInfo; } ;

/* Variables and functions */
 int APCI1710_CHRONOMETER ; 
#define  APCI1710_CHRONO_READ_CHANNEL 131 
#define  APCI1710_CHRONO_READ_PORT 130 
#define  APCI1710_CHRONO_SET_CHANNELOFF 129 
#define  APCI1710_CHRONO_SET_CHANNELON 128 
 unsigned char CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

int i_APCI1710_InsnBitsChronoDigitalIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned char b_ModulNbr, b_OutputChannel, b_InputChannel, b_IOType;
	unsigned int dw_Status;
	unsigned char *pb_ChannelStatus;
	unsigned char *pb_PortValue;

	b_ModulNbr = CR_AREF(insn->chanspec);
	i_ReturnValue = insn->n;
	b_IOType = (unsigned char) data[0];

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /***********************/
		/* Test if chronometer */
	   /***********************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_CHRONOMETER) {
	      /***********************************/
			/* Test if chronometer initialised */
	      /***********************************/

			if (devpriv->s_ModuleInfo[b_ModulNbr].
				s_ChronoModuleInfo.b_ChronoInit == 1) {
		 /***********************************/
				/* Test the digital output channel */
		 /***********************************/
				switch (b_IOType) {

				case APCI1710_CHRONO_SET_CHANNELOFF:

					b_OutputChannel =
						(unsigned char) CR_CHAN(insn->chanspec);
					if (b_OutputChannel <= 2) {

						outl(0, devpriv->s_BoardInfos.
							ui_Address + 20 +
							(b_OutputChannel * 4) +
							(64 * b_ModulNbr));
					}	/*  if ((b_OutputChannel >= 0) && (b_OutputChannel <= 2)) */
					else {
		    /****************************************/
						/* The selected digital output is wrong */
		    /****************************************/

						DPRINTK("The selected digital output is wrong\n");
						i_ReturnValue = -4;

					}	/*  if ((b_OutputChannel >= 0) && (b_OutputChannel <= 2)) */

					break;

				case APCI1710_CHRONO_SET_CHANNELON:

					b_OutputChannel =
						(unsigned char) CR_CHAN(insn->chanspec);
					if (b_OutputChannel <= 2) {

						outl(1, devpriv->s_BoardInfos.
							ui_Address + 20 +
							(b_OutputChannel * 4) +
							(64 * b_ModulNbr));
					}	/*  if ((b_OutputChannel >= 0) && (b_OutputChannel <= 2)) */
					else {
		    /****************************************/
						/* The selected digital output is wrong */
		    /****************************************/

						DPRINTK("The selected digital output is wrong\n");
						i_ReturnValue = -4;

					}	/*  if ((b_OutputChannel >= 0) && (b_OutputChannel <= 2)) */

					break;

				case APCI1710_CHRONO_READ_CHANNEL:
		 /**********************************/
					/* Test the digital input channel */
		 /**********************************/
					pb_ChannelStatus = (unsigned char *) &data[0];
					b_InputChannel =
						(unsigned char) CR_CHAN(insn->chanspec);

					if (b_InputChannel <= 2) {

						dw_Status =
							inl(devpriv->
							s_BoardInfos.
							ui_Address + 12 +
							(64 * b_ModulNbr));

						*pb_ChannelStatus =
							(unsigned char) (((dw_Status >>
									b_InputChannel)
								& 1) ^ 1);
					}	/*  if ((b_InputChannel >= 0) && (b_InputChannel <= 2)) */
					else {
		    /***************************************/
						/* The selected digital input is wrong */
		    /***************************************/

						DPRINTK("The selected digital input is wrong\n");
						i_ReturnValue = -4;
					}	/*  if ((b_InputChannel >= 0) && (b_InputChannel <= 2)) */

					break;

				case APCI1710_CHRONO_READ_PORT:

					pb_PortValue = (unsigned char *) &data[0];

					dw_Status =
						inl(devpriv->s_BoardInfos.
						ui_Address + 12 +
						(64 * b_ModulNbr));

					*pb_PortValue =
						(unsigned char) ((dw_Status & 0x7) ^ 7);
					break;
				}
			} else {
		 /*******************************/
				/* Chronometer not initialised */
		 /*******************************/

				DPRINTK("Chronometer not initialised\n");
				i_ReturnValue = -5;
			}
		} else {
	      /******************************************/
			/* The module is not a Chronometer module */
	      /******************************************/

			DPRINTK("The module is not a Chronometer module\n");
			i_ReturnValue = -3;
		}
	} else {
	   /***********************/
		/* Module number error */
	   /***********************/

		DPRINTK("Module number error\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}