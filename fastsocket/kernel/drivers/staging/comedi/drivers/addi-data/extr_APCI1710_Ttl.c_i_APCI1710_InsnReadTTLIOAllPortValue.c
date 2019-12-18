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
struct TYPE_5__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_8__ {TYPE_3__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_6__ {int b_TTLInit; int* b_PortConfiguration; } ;
struct TYPE_7__ {TYPE_2__ s_TTLIOInfo; } ;

/* Variables and functions */
 int APCI1710_TTL_IO ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_InsnReadTTLIOAllPortValue(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_StatusReg;
	unsigned char b_ModulNbr;
	unsigned int *pul_PortValue;

	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	i_ReturnValue = insn->n;
	pul_PortValue = (unsigned int *) &data[0];

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
	      /******************************************/
			/* Test if the TTL I/O module initialised */
	      /******************************************/

			if (devpriv->
				s_ModuleInfo[b_ModulNbr].
				s_TTLIOInfo.b_TTLInit == 1) {
		 /**************************/
				/* Read all digital input */
		 /**************************/

				dw_StatusReg = inl(devpriv->s_BoardInfos.
					ui_Address + (64 * b_ModulNbr));

		 /**********************/
				/* Test if TTL Rev1.0 */
		 /**********************/

				if ((devpriv->s_BoardInfos.
						dw_MolduleConfiguration
						[b_ModulNbr] & 0xFFFF) ==
					0x3130) {
					*pul_PortValue =
						dw_StatusReg & 0xFFFFFFUL;
				} else {
		    /**************************************/
					/* Test if port A not used for output */
		    /**************************************/

					if (devpriv->s_ModuleInfo[b_ModulNbr].
						s_TTLIOInfo.
						b_PortConfiguration[0] == 1) {
						*pul_PortValue =
							dw_StatusReg &
							0x3FFFF00UL;
					}

		    /**************************************/
					/* Test if port B not used for output */
		    /**************************************/

					if (devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_TTLIOInfo.
						b_PortConfiguration[1] == 1) {
						*pul_PortValue =
							dw_StatusReg &
							0x3FF00FFUL;
					}

		    /**************************************/
					/* Test if port C not used for output */
		    /**************************************/

					if (devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_TTLIOInfo.
						b_PortConfiguration[2] == 1) {
						*pul_PortValue =
							dw_StatusReg &
							0x300FFFFUL;
					}

		    /**************************************/
					/* Test if port D not used for output */
		    /**************************************/

					if (devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_TTLIOInfo.
						b_PortConfiguration[3] == 1) {
						*pul_PortValue =
							dw_StatusReg &
							0xFFFFFFUL;
					}
				}
			} else {
		 /***************************/
				/* TTL I/O not initialised */
		 /***************************/
				DPRINTK("TTL I/O not initialised\n");
				i_ReturnValue = -5;
			}
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