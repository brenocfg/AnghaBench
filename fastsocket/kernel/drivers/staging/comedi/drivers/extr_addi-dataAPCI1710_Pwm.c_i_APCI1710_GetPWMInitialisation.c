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
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__* s_ModuleInfo; TYPE_1__ s_BoardInfos; } ;
struct TYPE_8__ {TYPE_2__* s_PWMInfo; } ;
struct TYPE_9__ {TYPE_3__ s_PWMModuleInfo; } ;
struct TYPE_7__ {unsigned char b_TimingUnit; } ;

/* Variables and functions */
 int APCI1710_PWM ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_GetPWMInitialisation(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned char b_PWM,
	unsigned char *pb_TimingUnit,
	unsigned int *pul_LowTiming,
	unsigned int *pul_HighTiming,
	unsigned char *pb_StartLevel,
	unsigned char *pb_StopMode,
	unsigned char *pb_StopLevel,
	unsigned char *pb_ExternGate, unsigned char *pb_InterruptEnable, unsigned char *pb_Enable)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;
	unsigned int dw_Command;

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
					/* Read the low timing */
					/***********************/

					*pul_LowTiming =
						inl(devpriv->s_BoardInfos.
						ui_Address + 0 + (20 * b_PWM) +
						(64 * b_ModulNbr));

					/************************/
					/* Read the high timing */
					/************************/

					*pul_HighTiming =
						inl(devpriv->s_BoardInfos.
						ui_Address + 4 + (20 * b_PWM) +
						(64 * b_ModulNbr));

					/********************/
					/* Read the command */
					/********************/

					dw_Command = inl(devpriv->s_BoardInfos.
						ui_Address + 8 + (20 * b_PWM) +
						(64 * b_ModulNbr));

					*pb_StartLevel =
						(unsigned char) ((dw_Command >> 5) & 1);
					*pb_StopMode =
						(unsigned char) ((dw_Command >> 0) & 1);
					*pb_StopLevel =
						(unsigned char) ((dw_Command >> 1) & 1);
					*pb_ExternGate =
						(unsigned char) ((dw_Command >> 4) & 1);
					*pb_InterruptEnable =
						(unsigned char) ((dw_Command >> 3) & 1);

					if (*pb_StopLevel) {
						*pb_StopLevel =
							*pb_StopLevel +
							(unsigned char) ((dw_Command >>
								2) & 1);
					}

					/********************/
					/* Read the command */
					/********************/

					dw_Command = inl(devpriv->s_BoardInfos.
						ui_Address + 8 + (20 * b_PWM) +
						(64 * b_ModulNbr));

					*pb_Enable =
						(unsigned char) ((dw_Command >> 0) & 1);

					*pb_TimingUnit = devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_PWMModuleInfo.
						s_PWMInfo[b_PWM].b_TimingUnit;
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