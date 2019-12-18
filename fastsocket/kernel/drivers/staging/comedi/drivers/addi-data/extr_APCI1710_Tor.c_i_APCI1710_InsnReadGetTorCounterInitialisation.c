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
struct TYPE_6__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_8__ {TYPE_2__* s_TorCounterInfo; } ;
struct TYPE_9__ {TYPE_3__ s_TorCounterModuleInfo; } ;
struct TYPE_7__ {unsigned char b_TimingUnit; unsigned int ul_RealTimingInterval; } ;

/* Variables and functions */
 int APCI1710_TOR_COUNTER ; 
 unsigned char APCI1710_TOR_DOUBLE_MODE ; 
 unsigned char APCI1710_TOR_QUADRUPLE_MODE ; 
 unsigned char APCI1710_TOR_SIMPLE_MODE ; 
 unsigned char CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned char CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_InsnReadGetTorCounterInitialisation(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;
	unsigned char b_ModulNbr;
	unsigned char b_TorCounter;
	unsigned char *pb_TimingUnit;
	unsigned int *pul_TimingInterval;
	unsigned char *pb_InputMode;
	unsigned char *pb_ExternGate;
	unsigned char *pb_CycleMode;
	unsigned char *pb_Enable;
	unsigned char *pb_InterruptEnable;

	i_ReturnValue = insn->n;
	b_ModulNbr = CR_AREF(insn->chanspec);
	b_TorCounter = CR_CHAN(insn->chanspec);

	pb_TimingUnit = (unsigned char *) &data[0];
	pul_TimingInterval = (unsigned int *) &data[1];
	pb_InputMode = (unsigned char *) &data[2];
	pb_ExternGate = (unsigned char *) &data[3];
	pb_CycleMode = (unsigned char *) &data[4];
	pb_Enable = (unsigned char *) &data[5];
	pb_InterruptEnable = (unsigned char *) &data[6];

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /***********************/
		/* Test if tor counter */
	   /***********************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_TOR_COUNTER) {
	      /**********************************/
			/* Test the tor counter selection */
	      /**********************************/

			if (b_TorCounter <= 1) {

		 /***********************************/
				/* Test if tor counter initialised */
		 /***********************************/

				dw_Status = inl(devpriv->s_BoardInfos.
					ui_Address + 8 + (16 * b_TorCounter) +
					(64 * b_ModulNbr));

				if (dw_Status & 0x10) {
					*pb_Enable = dw_Status & 1;

		    /********************/
					/* Get the commando */
		    /********************/

					dw_Status = inl(devpriv->s_BoardInfos.
						ui_Address + 4 +
						(16 * b_TorCounter) +
						(64 * b_ModulNbr));

					*pb_CycleMode =
						(unsigned char) ((dw_Status >> 4) & 1);
					*pb_InterruptEnable =
						(unsigned char) ((dw_Status >> 5) & 1);

		    /******************************************************/
					/* Test if extern gate used for clock or for signal B */
		    /******************************************************/

					if (dw_Status & 0x600) {
		       /*****************************************/
						/* Test if extern gate used for signal B */
		       /*****************************************/

						if (dw_Status & 0x400) {
			  /***********************/
							/* Test if simple mode */
			  /***********************/

							if ((dw_Status & 0x7800)
								== 0x7800) {
								*pb_InputMode =
									APCI1710_TOR_SIMPLE_MODE;
							}

			  /***********************/
							/* Test if double mode */
			  /***********************/

							if ((dw_Status & 0x7800)
								== 0x1800) {
								*pb_InputMode =
									APCI1710_TOR_DOUBLE_MODE;
							}

			  /**************************/
							/* Test if quadruple mode */
			  /**************************/

							if ((dw_Status & 0x7800)
								== 0x0000) {
								*pb_InputMode =
									APCI1710_TOR_QUADRUPLE_MODE;
							}
						}	/*  if (dw_Status & 0x400) */
						else {
							*pb_InputMode = 1;
						}	/*  // if (dw_Status & 0x400) */

		       /************************/
						/* Extern gate not used */
		       /************************/

						*pb_ExternGate = 0;
					}	/*  if (dw_Status & 0x600) */
					else {
						*pb_InputMode =
							(unsigned char) ((dw_Status >> 6)
							& 1);
						*pb_ExternGate =
							(unsigned char) ((dw_Status >> 7)
							& 1);
					}	/*  if (dw_Status & 0x600) */

					*pb_TimingUnit =
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_TorCounterModuleInfo.
						s_TorCounterInfo[b_TorCounter].
						b_TimingUnit;

					*pul_TimingInterval =
						devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_TorCounterModuleInfo.
						s_TorCounterInfo[b_TorCounter].
						ul_RealTimingInterval;
				} else {
		    /*******************************/
					/* Tor counter not initialised */
		    /*******************************/

					DPRINTK("Tor counter not initialised\n");
					i_ReturnValue = -5;
				}

			}	/*  if (b_TorCounter <= 1) */
			else {
		 /**********************************/
				/* Tor counter selection is wrong */
		 /**********************************/

				DPRINTK("Tor counter selection is wrong \n");
				i_ReturnValue = -4;
			}	/*  if (b_TorCounter <= 1) */
		} else {
	      /******************************************/
			/* The module is not a tor counter module */
	      /******************************************/

			DPRINTK("The module is not a tor counter module\n");
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