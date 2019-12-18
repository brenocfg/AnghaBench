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
struct comedi_device {int dummy; } ;
struct TYPE_3__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_4__ {TYPE_1__ s_BoardInfos; } ;

/* Variables and functions */
 int APCI1710_PWM ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

int i_APCI1710_DisablePWM(struct comedi_device *dev, unsigned char b_ModulNbr, unsigned char b_PWM)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;

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
						/*******************/
						/* Disable the PWM */
						/*******************/
						outl(0, devpriv->s_BoardInfos.
							ui_Address + 12 +
							(20 * b_PWM) +
							(64 * b_ModulNbr));
					}	/*  if (dw_Status & 0x1) */
					else {
						/*******************/
						/* PWM not enabled */
						/*******************/
						DPRINTK("PWM not enabled\n");
						i_ReturnValue = -6;
					}	/*  if (dw_Status & 0x1) */
				}	/*  if (dw_Status & 0x10) */
				else {
					/***********************/
					/* PWM not initialised */
					/***********************/
					DPRINTK(" PWM not initialised\n");
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