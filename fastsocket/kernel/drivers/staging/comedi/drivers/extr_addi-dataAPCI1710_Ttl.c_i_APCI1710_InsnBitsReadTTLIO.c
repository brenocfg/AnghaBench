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
struct TYPE_5__ {int b_TTLInit; int /*<<< orphan*/ * b_PortConfiguration; } ;
struct TYPE_6__ {TYPE_1__ s_TTLIOInfo; } ;

/* Variables and functions */
 int APCI1710_TTL_IO ; 
#define  APCI1710_TTL_READCHANNEL 129 
#define  APCI1710_TTL_READPORT 128 
 unsigned char CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned char CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned char CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnBitsReadTTLIO(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_StatusReg;
	unsigned char b_ModulNbr;
	unsigned char b_SelectedPort;
	unsigned char b_InputChannel;
	unsigned char b_ReadType;
	unsigned char *pb_ChannelStatus;
	unsigned char *pb_PortValue;

	i_ReturnValue = insn->n;
	b_ReadType = (unsigned char) data[0];
	b_ModulNbr = CR_AREF(insn->chanspec);
	b_SelectedPort = CR_RANGE(insn->chanspec);
	b_InputChannel = CR_CHAN(insn->chanspec);

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /**************************/
		/* Test if TTL I/O module */
	   /**************************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_TTL_IO) {
			switch (b_ReadType) {

			case APCI1710_TTL_READCHANNEL:
				pb_ChannelStatus = (unsigned char *) &data[0];
	      /********************************/
				/* Test the TTL I/O port number */
	      /********************************/

				if (((b_SelectedPort <= 2)
						&& ((devpriv->s_BoardInfos.
								dw_MolduleConfiguration
								[b_ModulNbr] &
								0xFFFF) ==
							0x3130))
					|| ((b_SelectedPort <= 3)
						&& ((devpriv->s_BoardInfos.
								dw_MolduleConfiguration
								[b_ModulNbr] &
								0xFFFF) >=
							0x3230))) {
		 /******************************************/
					/* Test the digital imnput channel number */
		 /******************************************/

					if (((b_InputChannel <= 7)
							&& (b_SelectedPort < 3))
						|| ((b_InputChannel <= 1)
							&& (b_SelectedPort ==
								3))) {
		    /******************************************/
						/* Test if the TTL I/O module initialised */
		    /******************************************/

						if (devpriv->
							s_ModuleInfo
							[b_ModulNbr].
							s_TTLIOInfo.b_TTLInit ==
							1) {
		       /***********************************/
							/* Test if TTL port used for input */
		       /***********************************/

							if (((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF) == 0x3130) || (((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF) >= 0x3230) && (devpriv->s_ModuleInfo[b_ModulNbr].s_TTLIOInfo.b_PortConfiguration[b_SelectedPort] == 0))) {
			  /**************************/
								/* Read all digital input */
			  /**************************/

								dw_StatusReg =
									inl
									(devpriv->
									s_BoardInfos.
									ui_Address
									+
									(64 * b_ModulNbr));

								*pb_ChannelStatus
									=
									(unsigned char) (
									(dw_StatusReg
										>>
										(8 * b_SelectedPort)) >> b_InputChannel) & 1;
							} else {
			  /*******************************/
								/* Selected TTL I/O port error */
			  /*******************************/

								DPRINTK("Selected TTL I/O port error\n");
								i_ReturnValue =
									-4;
							}
						} else {
		       /***************************/
							/* TTL I/O not initialised */
		       /***************************/

							DPRINTK("TTL I/O not initialised\n");
							i_ReturnValue = -6;
						}
					} else {
		    /********************************/
						/* Selected digital input error */
		    /********************************/

						DPRINTK("Selected digital input error\n");
						i_ReturnValue = -5;
					}
				} else {
		 /*******************************/
					/* Selected TTL I/O port error */
		 /*******************************/

					DPRINTK("Selected TTL I/O port error\n");
					i_ReturnValue = -4;
				}
				break;

			case APCI1710_TTL_READPORT:
				pb_PortValue = (unsigned char *) &data[0];
			  /********************************/
				/* Test the TTL I/O port number */
			  /********************************/

				if (((b_SelectedPort <= 2)
						&& ((devpriv->s_BoardInfos.
								dw_MolduleConfiguration
								[b_ModulNbr] &
								0xFFFF) ==
							0x3130))
					|| ((b_SelectedPort <= 3)
						&& ((devpriv->s_BoardInfos.
								dw_MolduleConfiguration
								[b_ModulNbr] &
								0xFFFF) >=
							0x3230))) {
		 /******************************************/
					/* Test if the TTL I/O module initialised */
		 /******************************************/

					if (devpriv->s_ModuleInfo[b_ModulNbr].
						s_TTLIOInfo.b_TTLInit == 1) {
		    /***********************************/
						/* Test if TTL port used for input */
		    /***********************************/

						if (((devpriv->s_BoardInfos.
									dw_MolduleConfiguration
									[b_ModulNbr]
									&
									0xFFFF)
								== 0x3130)
							|| (((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF) >= 0x3230) && (devpriv->s_ModuleInfo[b_ModulNbr].s_TTLIOInfo.b_PortConfiguration[b_SelectedPort] == 0))) {
		       /**************************/
							/* Read all digital input */
		       /**************************/

							dw_StatusReg =
								inl(devpriv->
								s_BoardInfos.
								ui_Address +
								(64 * b_ModulNbr));

							*pb_PortValue =
								(unsigned char) (
								(dw_StatusReg >>
									(8 * b_SelectedPort)) & 0xFF);
						} else {
		       /*******************************/
							/* Selected TTL I/O port error */
		       /*******************************/

							DPRINTK("Selected TTL I/O port error\n");
							i_ReturnValue = -4;
						}
					} else {
		    /***************************/
						/* TTL I/O not initialised */
		    /***************************/

						DPRINTK("TTL I/O not initialised\n");
						i_ReturnValue = -5;
					}
				} else {
		 /*******************************/
					/* Selected TTL I/O port error */
		 /*******************************/

					DPRINTK("Selected TTL I/O port error\n");
					i_ReturnValue = -4;
				}
				break;

			default:
				printk("Bad ReadType\n");

			}	/* End Switch */
		} else {
	      /**********************************/
			/* The module is not a TTL module */
	      /**********************************/

			DPRINTK("The module is not a TTL module\n");
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