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
struct TYPE_7__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_6__ {size_t ui_Read; TYPE_1__* s_FIFOInterruptParameters; } ;
struct TYPE_8__ {TYPE_3__ s_BoardInfos; TYPE_2__ s_InterruptParameters; } ;
struct TYPE_5__ {unsigned int b_OldModuleMask; unsigned int ul_OldInterruptMask; unsigned int ul_OldCounterLatchValue; } ;

/* Variables and functions */
 int APCI1710_SAVE_INTERRUPT ; 
 int APCI1710_TOR_COUNTER ; 
#define  APCI1710_TOR_GETCOUNTERVALUE 129 
#define  APCI1710_TOR_GETPROGRESSSTATUS 128 
 unsigned char APCI1710_TOR_READINTERRUPT ; 
 unsigned char CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_4__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1710_InsnBitsGetTorCounterProgressStatusAndValue(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = 0;
	unsigned int dw_Status;
	unsigned int dw_TimeOut = 0;

	unsigned char b_ModulNbr;
	unsigned char b_TorCounter;
	unsigned char b_ReadType;
	unsigned int ui_TimeOut;
	unsigned char *pb_TorCounterStatus;
	unsigned int *pul_TorCounterValue;

	i_ReturnValue = insn->n;
	b_ModulNbr = CR_AREF(insn->chanspec);
	b_ReadType = (unsigned char) data[0];
	b_TorCounter = (unsigned char) data[1];
	ui_TimeOut = (unsigned int) data[2];
	pb_TorCounterStatus = (unsigned char *) &data[0];
	pul_TorCounterValue = (unsigned int *) &data[1];

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ReadType == APCI1710_TOR_READINTERRUPT) {

		data[0] = devpriv->s_InterruptParameters.
			s_FIFOInterruptParameters[devpriv->
			s_InterruptParameters.ui_Read].b_OldModuleMask;
		data[1] = devpriv->s_InterruptParameters.
			s_FIFOInterruptParameters[devpriv->
			s_InterruptParameters.ui_Read].ul_OldInterruptMask;
		data[2] = devpriv->s_InterruptParameters.
			s_FIFOInterruptParameters[devpriv->
			s_InterruptParameters.ui_Read].ul_OldCounterLatchValue;

			   /**************************/
		/* Increment the read FIFO */
			   /***************************/

		devpriv->
			s_InterruptParameters.
			ui_Read = (devpriv->
			s_InterruptParameters.
			ui_Read + 1) % APCI1710_SAVE_INTERRUPT;

		return insn->n;
	}

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

		 /*******************************/
				/* Test if counter initialised */
		 /*******************************/

				if (dw_Status & 0x10) {
		    /***************************/
					/* Test if counter enabled */
		    /***************************/

					if (dw_Status & 0x1) {

						switch (b_ReadType) {

						case APCI1710_TOR_GETPROGRESSSTATUS:
		       /*******************/
							/* Read the status */
		       /*******************/

							dw_Status =
								inl(devpriv->
								s_BoardInfos.
								ui_Address + 4 +
								(16 * b_TorCounter) + (64 * b_ModulNbr));

							dw_Status =
								dw_Status & 0xF;

		       /*****************/
							/* Test if start */
		       /*****************/

							if (dw_Status & 1) {
								if (dw_Status &
									2) {
									if (dw_Status & 4) {
				/************************/
										/* Tor counter owerflow */
				/************************/

										*pb_TorCounterStatus
											=
											3;
									} else {
				/***********************/
										/* Tor counter started */
				/***********************/

										*pb_TorCounterStatus
											=
											2;
									}
								} else {
			     /***********************/
									/* Tor counter started */
			     /***********************/

									*pb_TorCounterStatus
										=
										1;
								}
							} else {
			  /***************************/
								/* Tor counter not started */
			  /***************************/

								*pb_TorCounterStatus
									= 0;
							}
							break;

						case APCI1710_TOR_GETCOUNTERVALUE:

		       /*****************************/
							/* Test the timout parameter */
		       /*****************************/

							if ((ui_TimeOut >= 0)
								&& (ui_TimeOut
									<=
									65535UL))
							{
								for (;;) {
			     /*******************/
									/* Read the status */
			     /*******************/

									dw_Status
										=
										inl
										(devpriv->
										s_BoardInfos.
										ui_Address
										+
										4
										+
										(16 * b_TorCounter) + (64 * b_ModulNbr));
			     /********************/
									/* Test if overflow */
			     /********************/

									if ((dw_Status & 4) == 4) {
				/******************/
										/* Overflow occur */
				/******************/

										*pb_TorCounterStatus
											=
											3;

				/******************/
										/* Read the value */
				/******************/

										*pul_TorCounterValue
											=
											inl
											(devpriv->
											s_BoardInfos.
											ui_Address
											+
											0
											+
											(16 * b_TorCounter) + (64 * b_ModulNbr));
										break;
									}	/*  if ((dw_Status & 4) == 4) */
									else {
				/*******************************/
										/* Test if measurement stopped */
				/*******************************/

										if ((dw_Status & 2) == 2) {
				   /***********************/
											/* A stop signal occur */
				   /***********************/

											*pb_TorCounterStatus
												=
												2;

				   /******************/
											/* Read the value */
				   /******************/

											*pul_TorCounterValue
												=
												inl
												(devpriv->
												s_BoardInfos.
												ui_Address
												+
												0
												+
												(16 * b_TorCounter) + (64 * b_ModulNbr));

											break;
										}	/*  if ((dw_Status & 2) == 2) */
										else {
				   /*******************************/
											/* Test if measurement started */
				   /*******************************/

											if ((dw_Status & 1) == 1) {
				      /************************/
												/* A start signal occur */
				      /************************/

												*pb_TorCounterStatus
													=
													1;
											}	/*  if ((dw_Status & 1) == 1) */
											else {
				      /***************************/
												/* Measurement not started */
				      /***************************/

												*pb_TorCounterStatus
													=
													0;
											}	/*  if ((dw_Status & 1) == 1) */
										}	/*  if ((dw_Status & 2) == 2) */
									}	/*  if ((dw_Status & 8) == 8) */

									if (dw_TimeOut == ui_TimeOut) {
				/*****************/
										/* Timeout occur */
				/*****************/

										break;
									} else {
				/*************************/
										/* Increment the timeout */
				/*************************/

										dw_TimeOut
											=
											dw_TimeOut
											+
											1;

										mdelay(1000);
									}
								}	/*  for (;;) */

			  /*************************/
								/* Test if timeout occur */
			  /*************************/

								if ((*pb_TorCounterStatus != 3) && (dw_TimeOut == ui_TimeOut) && (ui_TimeOut != 0)) {
			     /*****************/
									/* Timeout occur */
			     /*****************/

									*pb_TorCounterStatus
										=
										4;
								}
							} else {
			  /******************************/
								/* Timeout parameter is wrong */
			  /******************************/

								DPRINTK("Timeout parameter is wrong\n");
								i_ReturnValue =
									-7;
							}
							break;

						default:
							printk("Inputs wrong\n");
						}	/*  switch end */
					}	/*  if (dw_Status & 0x1) */
					else {
		       /***************************/
						/* Tor counter not enabled */
		       /***************************/

						DPRINTK("Tor counter not enabled\n");
						i_ReturnValue = -6;
					}	/*  if (dw_Status & 0x1) */
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

				DPRINTK("Tor counter selection is wrong\n");
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