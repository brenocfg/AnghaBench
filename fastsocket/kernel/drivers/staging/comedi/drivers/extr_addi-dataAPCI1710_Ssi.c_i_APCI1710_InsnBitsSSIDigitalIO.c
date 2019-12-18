#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_3__ {int* dw_MolduleConfiguration; int /*<<< orphan*/  ui_Address; } ;
struct TYPE_4__ {TYPE_1__ s_BoardInfos; } ;

/* Variables and functions */
 int APCI1710_SSI_COUNTER ; 
#define  APCI1710_SSI_READ_1CHANNEL 131 
#define  APCI1710_SSI_READ_ALLCHANNEL 130 
#define  APCI1710_SSI_SET_CHANNELOFF 129 
#define  APCI1710_SSI_SET_CHANNELON 128 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnBitsSSIDigitalIO(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_StatusReg;
	unsigned char b_ModulNbr;
	unsigned char b_InputChannel;
	unsigned char *pb_ChannelStatus;
	unsigned char *pb_InputStatus;
	unsigned char b_IOType;
	i_ReturnValue = insn->n;
	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_IOType = (unsigned char) data[0];

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /***********************/
		/* Test if SSI counter */
	   /***********************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_SSI_COUNTER) {
			switch (b_IOType) {
			case APCI1710_SSI_SET_CHANNELON:
					/*****************************/
				/* Set the digital output ON */
					/*****************************/

				outl(1, devpriv->s_BoardInfos.ui_Address + 16 +
					(64 * b_ModulNbr));
				break;

			case APCI1710_SSI_SET_CHANNELOFF:
					/******************************/
				/* Set the digital output OFF */
					/******************************/

				outl(0, devpriv->s_BoardInfos.ui_Address + 16 +
					(64 * b_ModulNbr));
				break;

			case APCI1710_SSI_READ_1CHANNEL:
				   /******************************************/
				/* Test the digital imnput channel number */
				   /******************************************/

				b_InputChannel = (unsigned char) CR_CHAN(insn->chanspec);
				pb_ChannelStatus = (unsigned char *) &data[0];

				if (b_InputChannel <= 2) {
					/**************************/
					/* Read all digital input */
					/**************************/

					dw_StatusReg =
						inl(devpriv->s_BoardInfos.
						ui_Address + (64 * b_ModulNbr));
					*pb_ChannelStatus =
						(unsigned char) (((~dw_StatusReg) >> (4 +
								b_InputChannel))
						& 1);
				} else {
					/********************************/
					/* Selected digital input error */
					/********************************/

					DPRINTK("Selected digital input error\n");
					i_ReturnValue = -4;
				}
				break;

			case APCI1710_SSI_READ_ALLCHANNEL:
					/**************************/
				/* Read all digital input */
					/**************************/
				pb_InputStatus = (unsigned char *) &data[0];

				dw_StatusReg =
					inl(devpriv->s_BoardInfos.ui_Address +
					(64 * b_ModulNbr));
				*pb_InputStatus =
					(unsigned char) (((~dw_StatusReg) >> 4) & 7);
				break;

			default:
				printk("IO type wrong\n");

			}	/* switch end */
		} else {
	      /**********************************/
			/* The module is not a SSI module */
	      /**********************************/

			DPRINTK("The module is not a SSI module\n");
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