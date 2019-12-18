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
struct TYPE_5__ {int b_TTLInit; int* b_PortConfiguration; } ;
struct TYPE_6__ {TYPE_1__ s_TTLIOInfo; } ;

/* Variables and functions */
#define  APCI1710_TTL_INIT 129 
#define  APCI1710_TTL_INITDIRECTION 128 
 int APCI1710_TTL_IO ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 int /*<<< orphan*/  outl (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnConfigInitTTLIO(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned char b_ModulNbr;
	unsigned char b_InitType;
	unsigned char b_PortAMode;
	unsigned char b_PortBMode;
	unsigned char b_PortCMode;
	unsigned char b_PortDMode;

	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_InitType = (unsigned char) data[0];
	i_ReturnValue = insn->n;

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
			switch (b_InitType) {
			case APCI1710_TTL_INIT:

				devpriv->s_ModuleInfo[b_ModulNbr].
					s_TTLIOInfo.b_TTLInit = 1;

	      /***************************/
				/* Set TTL port A to input */
	      /***************************/

				devpriv->s_ModuleInfo[b_ModulNbr].
					s_TTLIOInfo.b_PortConfiguration[0] = 0;

	      /***************************/
				/* Set TTL port B to input */
	      /***************************/

				devpriv->s_ModuleInfo[b_ModulNbr].
					s_TTLIOInfo.b_PortConfiguration[1] = 0;

	      /***************************/
				/* Set TTL port C to input */
	      /***************************/

				devpriv->s_ModuleInfo[b_ModulNbr].
					s_TTLIOInfo.b_PortConfiguration[2] = 0;

	      /****************************/
				/* Set TTL port D to output */
	      /****************************/

				devpriv->s_ModuleInfo[b_ModulNbr].
					s_TTLIOInfo.b_PortConfiguration[3] = 1;

	      /*************************/
				/* Set the configuration */
	      /*************************/

				outl(0x8,
					devpriv->s_BoardInfos.ui_Address + 20 +
					(64 * b_ModulNbr));
				break;

			case APCI1710_TTL_INITDIRECTION:

				b_PortAMode = (unsigned char) data[1];
				b_PortBMode = (unsigned char) data[2];
				b_PortCMode = (unsigned char) data[3];
				b_PortDMode = (unsigned char) data[4];

	      /********************/
				/* Test the version */
	      /********************/

				if ((devpriv->s_BoardInfos.
						dw_MolduleConfiguration
						[b_ModulNbr] & 0xFFFF) >=
					0x3230) {
		 /************************/
					/* Test the port A mode */
		 /************************/

					if ((b_PortAMode == 0)
						|| (b_PortAMode == 1)) {
		    /************************/
						/* Test the port B mode */
		    /************************/

						if ((b_PortBMode == 0)
							|| (b_PortBMode == 1)) {
		       /************************/
							/* Test the port C mode */
		       /************************/

							if ((b_PortCMode == 0)
								|| (b_PortCMode
									== 1)) {
			  /************************/
								/* Test the port D mode */
			  /************************/

								if ((b_PortDMode == 0) || (b_PortDMode == 1)) {
									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_TTLIOInfo.
										b_TTLInit
										=
										1;

			     /***********************/
									/* Set TTL port A mode */
			     /***********************/

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_TTLIOInfo.
										b_PortConfiguration
										[0]
										=
										b_PortAMode;

			     /***********************/
									/* Set TTL port B mode */
			     /***********************/

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_TTLIOInfo.
										b_PortConfiguration
										[1]
										=
										b_PortBMode;

			     /***********************/
									/* Set TTL port C mode */
			     /***********************/

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_TTLIOInfo.
										b_PortConfiguration
										[2]
										=
										b_PortCMode;

			     /***********************/
									/* Set TTL port D mode */
			     /***********************/

									devpriv->
										s_ModuleInfo
										[b_ModulNbr].
										s_TTLIOInfo.
										b_PortConfiguration
										[3]
										=
										b_PortDMode;

			     /*************************/
									/* Set the configuration */
			     /*************************/

									outl((b_PortAMode << 0) | (b_PortBMode << 1) | (b_PortCMode << 2) | (b_PortDMode << 3), devpriv->s_BoardInfos.ui_Address + 20 + (64 * b_ModulNbr));
								} else {
			     /**********************************/
									/* Port D mode selection is wrong */
			     /**********************************/

									DPRINTK("Port D mode selection is wrong\n");
									i_ReturnValue
										=
										-8;
								}
							} else {
			  /**********************************/
								/* Port C mode selection is wrong */
			  /**********************************/

								DPRINTK("Port C mode selection is wrong\n");
								i_ReturnValue =
									-7;
							}
						} else {
		       /**********************************/
							/* Port B mode selection is wrong */
		       /**********************************/

							DPRINTK("Port B mode selection is wrong\n");
							i_ReturnValue = -6;
						}
					} else {
		    /**********************************/
						/* Port A mode selection is wrong */
		    /**********************************/

						DPRINTK("Port A mode selection is wrong\n");
						i_ReturnValue = -5;
					}
				} else {
		 /*******************************************/
					/* Function not available for this version */
		 /*******************************************/

					DPRINTK("Function not available for this version\n");
					i_ReturnValue = -4;
				}
				break;

				DPRINTK("\n");
			default:
				printk("Bad Config Type\n");
			}	/*  switch end */
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