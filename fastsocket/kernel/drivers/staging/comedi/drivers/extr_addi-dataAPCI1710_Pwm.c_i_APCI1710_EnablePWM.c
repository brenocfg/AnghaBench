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
struct TYPE_9__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__ s_BoardInfos; TYPE_3__* s_ModuleInfo; int /*<<< orphan*/  tsk_Current; } ;
struct TYPE_7__ {TYPE_1__* s_PWMInfo; } ;
struct TYPE_8__ {TYPE_2__ s_PWMModuleInfo; } ;
struct TYPE_6__ {unsigned char b_InterruptEnable; } ;

/* Variables and functions */
 unsigned char APCI1710_DISABLE ; 
 unsigned char APCI1710_ENABLE ; 
 int APCI1710_PWM ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  current ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI1710_EnablePWM(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned char b_PWM,
	unsigned char b_StartLevel,
	unsigned char b_StopMode,
	unsigned char b_StopLevel, unsigned char b_ExternGate, unsigned char b_InterruptEnable)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;
	unsigned int dw_Command;

	devpriv->tsk_Current = current;	/*  Save the current process task structure */
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
					/**********************************/
					/* Test the start level selection */
					/**********************************/

					if (b_StartLevel <= 1) {
						/**********************/
						/* Test the stop mode */
						/**********************/

						if (b_StopMode <= 1) {
							/***********************/
							/* Test the stop level */
							/***********************/

							if (b_StopLevel <= 2) {
								/*****************************/
								/* Test the extern gate mode */
								/*****************************/

								if (b_ExternGate
									<= 1) {
									/*****************************/
									/* Test the interrupt action */
									/*****************************/

									if (b_InterruptEnable == APCI1710_ENABLE || b_InterruptEnable == APCI1710_DISABLE) {
										/******************************************/
										/* Test if interrupt function initialised */
										/******************************************/

										/********************/
										/* Read the command */
										/********************/

										dw_Command
											=
											inl
											(devpriv->
											s_BoardInfos.
											ui_Address
											+
											8
											+
											(20 * b_PWM) + (64 * b_ModulNbr));

										dw_Command
											=
											dw_Command
											&
											0x80;

										/********************/
										/* Make the command */
										/********************/

										dw_Command
											=
											dw_Command
											|
											b_StopMode
											|
											(b_InterruptEnable
											<<
											3)
											|
											(b_ExternGate
											<<
											4)
											|
											(b_StartLevel
											<<
											5);

										if (b_StopLevel & 3) {
											dw_Command
												=
												dw_Command
												|
												2;

											if (b_StopLevel & 2) {
												dw_Command
													=
													dw_Command
													|
													4;
											}
										}

										devpriv->
											s_ModuleInfo
											[b_ModulNbr].
											s_PWMModuleInfo.
											s_PWMInfo
											[b_PWM].
											b_InterruptEnable
											=
											b_InterruptEnable;

										/*******************/
										/* Set the command */
										/*******************/

										outl(dw_Command, devpriv->s_BoardInfos.ui_Address + 8 + (20 * b_PWM) + (64 * b_ModulNbr));

										/******************/
										/* Enable the PWM */
										/******************/
										outl(1, devpriv->s_BoardInfos.ui_Address + 12 + (20 * b_PWM) + (64 * b_ModulNbr));
									}	/*  if (b_InterruptEnable == APCI1710_ENABLE || b_InterruptEnable == APCI1710_DISABLE) */
									else {
										/********************************/
										/* Interrupt parameter is wrong */
										/********************************/
										DPRINTK("Interrupt parameter is wrong\n");
										i_ReturnValue
											=
											-10;
									}	/*  if (b_InterruptEnable == APCI1710_ENABLE || b_InterruptEnable == APCI1710_DISABLE) */
								}	/*  if (b_ExternGate >= 0 && b_ExternGate <= 1) */
								else {
									/*****************************************/
									/* Extern gate signal selection is wrong */
									/*****************************************/
									DPRINTK("Extern gate signal selection is wrong\n");
									i_ReturnValue
										=
										-9;
								}	/*  if (b_ExternGate >= 0 && b_ExternGate <= 1) */
							}	/*  if (b_StopLevel >= 0 && b_StopLevel <= 2) */
							else {
								/*************************************/
								/* PWM stop level selection is wrong */
								/*************************************/
								DPRINTK("PWM stop level selection is wrong\n");
								i_ReturnValue =
									-8;
							}	/*  if (b_StopLevel >= 0 && b_StopLevel <= 2) */
						}	/*  if (b_StopMode >= 0 && b_StopMode <= 1) */
						else {
							/************************************/
							/* PWM stop mode selection is wrong */
							/************************************/
							DPRINTK("PWM stop mode selection is wrong\n");
							i_ReturnValue = -7;
						}	/*  if (b_StopMode >= 0 && b_StopMode <= 1) */
					}	/*  if (b_StartLevel >= 0 && b_StartLevel <= 1) */
					else {
						/**************************************/
						/* PWM start level selection is wrong */
						/**************************************/
						DPRINTK("PWM start level selection is wrong\n");
						i_ReturnValue = -6;
					}	/*  if (b_StartLevel >= 0 && b_StartLevel <= 1) */
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