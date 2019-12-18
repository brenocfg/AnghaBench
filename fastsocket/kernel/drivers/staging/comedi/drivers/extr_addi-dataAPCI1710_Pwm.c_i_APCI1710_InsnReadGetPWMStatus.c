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
struct TYPE_3__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_4__ {TYPE_1__ s_BoardInfos; } ;

/* Variables and functions */
 int APCI1710_PWM ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_InsnReadGetPWMStatus(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;

	unsigned char b_ModulNbr;
	unsigned char b_PWM;
	unsigned char *pb_PWMOutputStatus;
	unsigned char *pb_ExternGateStatus;

	i_ReturnValue = insn->n;
	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_PWM = (unsigned char) CR_CHAN(insn->chanspec);
	pb_PWMOutputStatus = (unsigned char *) &data[0];
	pb_ExternGateStatus = (unsigned char *) &data[1];

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
		/***************/
		/* Test if PWM */
		/***************/

		if ((devpriv->s_BoardInfos.
				dw_MolduleConfiguration[b_ModulNbr] &
				0xFFFF0000UL) == APCI1710_PWM) {
			/**************************/
			/* Test the PWM selection */
			/**************************/

			if (b_PWM <= 1) {
				/***************************/
				/* Test if PWM initialised */
				/***************************/

				dw_Status = inl(devpriv->s_BoardInfos.
					ui_Address + 12 + (20 * b_PWM) +
					(64 * b_ModulNbr));

				if (dw_Status & 0x10) {
					/***********************/
					/* Test if PWM enabled */
					/***********************/

					if (dw_Status & 0x1) {
						*pb_PWMOutputStatus =
							(unsigned char) ((dw_Status >> 7)
							& 1);
						*pb_ExternGateStatus =
							(unsigned char) ((dw_Status >> 6)
							& 1);
					}	/*  if (dw_Status & 0x1) */
					else {
						/*******************/
						/* PWM not enabled */
						/*******************/

						DPRINTK("PWM not enabled \n");
						i_ReturnValue = -6;
					}	/*  if (dw_Status & 0x1) */
				}	/*  if (dw_Status & 0x10) */
				else {
					/***********************/
					/* PWM not initialised */
					/***********************/

					DPRINTK("PWM not initialised\n");
					i_ReturnValue = -5;
				}	/*  if (dw_Status & 0x10) */
			}	/*  if (b_PWM >= 0 && b_PWM <= 1) */
			else {
				/******************************/
				/* Tor PWM selection is wrong */
				/******************************/

				DPRINTK("Tor PWM selection is wrong\n");
				i_ReturnValue = -4;
			}	/*  if (b_PWM >= 0 && b_PWM <= 1) */
		} else {
			/**********************************/
			/* The module is not a PWM module */
			/**********************************/

			DPRINTK("The module is not a PWM module\n");
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