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
struct comedi_device {size_t minor; } ;
struct TYPE_4__ {int /*<<< orphan*/  tsk_Current; scalar_t__ iobase; } ;
struct TYPE_3__ {int i_ScanType; unsigned int* ui_InterruptChannelValue; size_t i_Count; unsigned int ui_Channel_num; int /*<<< orphan*/  i_Sum; int /*<<< orphan*/  i_ChannelCount; int /*<<< orphan*/  i_InterruptFlag; int /*<<< orphan*/  i_ADDIDATAGain; int /*<<< orphan*/  i_CJCGain; int /*<<< orphan*/  i_ADDIDATAPolarity; int /*<<< orphan*/  i_CJCPolarity; scalar_t__ i_Offset; int /*<<< orphan*/  i_ADDIDATAType; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGIO ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i_APCI3200_InterruptHandleEos (struct comedi_device*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCJCCalGain (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCJCCalOffset (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCJCValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCalibrationGainValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCalibrationOffsetValue (struct comedi_device*,unsigned int*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 TYPE_1__* s_BoardInfos ; 
 int send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void v_APCI3200_Interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned int ui_StatusRegister = 0;
	unsigned int ui_ChannelNumber = 0;
	int i_CalibrationFlag = 0;
	int i_CJCFlag = 0;
	unsigned int ui_DummyValue = 0;
	unsigned int ui_DigitalTemperature = 0;
	unsigned int ui_DigitalInput = 0;
	int i_ConvertCJCCalibration;

	/* BEGIN JK TEST */
	int i_ReturnValue = 0;
	/* END JK TEST */

	/* printk ("\n i_ScanType = %i i_ADDIDATAType = %i", s_BoardInfos [dev->minor].i_ScanType, s_BoardInfos [dev->minor].i_ADDIDATAType); */

	/* switch(i_ScanType) */
	switch (s_BoardInfos[dev->minor].i_ScanType) {
	case 0:
	case 1:
		/* switch(i_ADDIDATAType) */
		switch (s_BoardInfos[dev->minor].i_ADDIDATAType) {
		case 0:
		case 1:

	  /************************************/
			/*Read the interrupt status register */
	  /************************************/
			/* ui_StatusRegister = inl(devpriv->iobase+i_Offset + 16); */
			ui_StatusRegister =
				inl(devpriv->iobase +
				s_BoardInfos[dev->minor].i_Offset + 16);
			if ((ui_StatusRegister & 0x2) == 0x2) {
				/* i_CalibrationFlag = ((inl(devpriv->iobase+i_Offset + 12) & 0x00060000) >> 17); */
				i_CalibrationFlag =
					((inl(devpriv->iobase +
							s_BoardInfos[dev->
								minor].
							i_Offset +
							12) & 0x00060000) >>
					17);
	      /*************************/
				/*Read the channel number */
	      /*************************/
				/* ui_ChannelNumber = inl(devpriv->iobase+i_Offset + 24); */

	      /*************************************/
				/*Read the digital analog input value */
	      /*************************************/
				/* ui_DigitalInput = inl(devpriv->iobase+i_Offset + 28); */
				ui_DigitalInput =
					inl(devpriv->iobase +
					s_BoardInfos[dev->minor].i_Offset + 28);

	      /***********************************************/
				/* Test if the value read is the channel value */
	      /***********************************************/
				if (i_CalibrationFlag == 0) {
					/* ui_InterruptChannelValue[i_Count + 0] = ui_DigitalInput; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 0] = ui_DigitalInput;

					/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
					/*
					   printk("\n 1 - i_APCI3200_GetChannelCalibrationValue (dev, s_BoardInfos %i", ui_ChannelNumber);
					   i_APCI3200_GetChannelCalibrationValue (dev, s_BoardInfos [dev->minor].ui_Channel_num,
					   &s_BoardInfos [dev->minor].ui_InterruptChannelValue[s_BoardInfos [dev->minor].i_Count + 6],
					   &s_BoardInfos [dev->minor].ui_InterruptChannelValue[s_BoardInfos [dev->minor].i_Count + 7],
					   &s_BoardInfos [dev->minor].ui_InterruptChannelValue[s_BoardInfos [dev->minor].i_Count + 8]);
					 */
					/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

		  /******************************************************/
					/*Start the conversion of the calibration offset value */
		  /******************************************************/
					i_APCI3200_ReadCalibrationOffsetValue
						(dev, &ui_DummyValue);
				}	/* if (i_CalibrationFlag == 0) */
	      /**********************************************************/
				/* Test if the value read is the calibration offset value */
	      /**********************************************************/

				if (i_CalibrationFlag == 1) {

		  /******************/
					/* Save the value */
		  /******************/

					/* ui_InterruptChannelValue[i_Count + 1] = ui_DigitalInput; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 1] = ui_DigitalInput;

		  /******************************************************/
					/* Start the conversion of the calibration gain value */
		  /******************************************************/
					i_APCI3200_ReadCalibrationGainValue(dev,
						&ui_DummyValue);
				}	/* if (i_CalibrationFlag == 1) */
	      /******************************************************/
				/*Test if the value read is the calibration gain value */
	      /******************************************************/

				if (i_CalibrationFlag == 2) {

		  /****************/
					/*Save the value */
		  /****************/
					/* ui_InterruptChannelValue[i_Count + 2] = ui_DigitalInput; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 2] = ui_DigitalInput;
					/* if(i_ScanType==1) */
					if (s_BoardInfos[dev->minor].
						i_ScanType == 1) {

						/* i_InterruptFlag=0; */
						s_BoardInfos[dev->minor].
							i_InterruptFlag = 0;
						/* i_Count=i_Count + 6; */
						/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
						/* s_BoardInfos [dev->minor].i_Count=s_BoardInfos [dev->minor].i_Count + 6; */
						s_BoardInfos[dev->minor].
							i_Count =
							s_BoardInfos[dev->
							minor].i_Count + 9;
						/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
					}	/* if(i_ScanType==1) */
					else {
						/* i_Count=0; */
						s_BoardInfos[dev->minor].
							i_Count = 0;
					}	/* elseif(i_ScanType==1) */
					/* if(i_ScanType!=1) */
					if (s_BoardInfos[dev->minor].
						i_ScanType != 1) {
						i_ReturnValue = send_sig(SIGIO, devpriv->tsk_Current, 0);	/*  send signal to the sample */
					}	/* if(i_ScanType!=1) */
					else {
						/* if(i_ChannelCount==i_Sum) */
						if (s_BoardInfos[dev->minor].
							i_ChannelCount ==
							s_BoardInfos[dev->
								minor].i_Sum) {
							send_sig(SIGIO, devpriv->tsk_Current, 0);	/*  send signal to the sample */
						}
					}	/* if(i_ScanType!=1) */
				}	/* if (i_CalibrationFlag == 2) */
			}	/*  if ((ui_StatusRegister & 0x2) == 0x2) */

			break;

		case 2:
	  /************************************/
			/*Read the interrupt status register */
	  /************************************/

			/* ui_StatusRegister = inl(devpriv->iobase+i_Offset + 16); */
			ui_StatusRegister =
				inl(devpriv->iobase +
				s_BoardInfos[dev->minor].i_Offset + 16);
	  /*************************/
			/*Test if interrupt occur */
	  /*************************/

			if ((ui_StatusRegister & 0x2) == 0x2) {

				/* i_CJCFlag = ((inl(devpriv->iobase+i_Offset + 4) & 0x00000400) >> 10); */
				i_CJCFlag =
					((inl(devpriv->iobase +
							s_BoardInfos[dev->
								minor].
							i_Offset +
							4) & 0x00000400) >> 10);

				/* i_CalibrationFlag = ((inl(devpriv->iobase+i_Offset + 12) & 0x00060000) >> 17); */
				i_CalibrationFlag =
					((inl(devpriv->iobase +
							s_BoardInfos[dev->
								minor].
							i_Offset +
							12) & 0x00060000) >>
					17);

	      /*************************/
				/*Read the channel number */
	      /*************************/

				/* ui_ChannelNumber = inl(devpriv->iobase+i_Offset + 24); */
				ui_ChannelNumber =
					inl(devpriv->iobase +
					s_BoardInfos[dev->minor].i_Offset + 24);
				/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
				s_BoardInfos[dev->minor].ui_Channel_num =
					ui_ChannelNumber;
				/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

	      /************************************/
				/*Read the digital temperature value */
	      /************************************/
				/* ui_DigitalTemperature = inl(devpriv->iobase+i_Offset + 28); */
				ui_DigitalTemperature =
					inl(devpriv->iobase +
					s_BoardInfos[dev->minor].i_Offset + 28);

	      /*********************************************/
				/*Test if the value read is the channel value */
	      /*********************************************/

				if ((i_CalibrationFlag == 0)
					&& (i_CJCFlag == 0)) {
					/* ui_InterruptChannelValue[i_Count + 0]=ui_DigitalTemperature; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 0] =
						ui_DigitalTemperature;

		  /*********************************/
					/*Start the conversion of the CJC */
		  /*********************************/
					i_APCI3200_ReadCJCValue(dev,
						&ui_DummyValue);

				}	/* if ((i_CalibrationFlag == 0) && (i_CJCFlag == 0)) */

		 /*****************************************/
				/*Test if the value read is the CJC value */
		 /*****************************************/

				if ((i_CJCFlag == 1)
					&& (i_CalibrationFlag == 0)) {
					/* ui_InterruptChannelValue[i_Count + 3]=ui_DigitalTemperature; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 3] =
						ui_DigitalTemperature;

		  /******************************************************/
					/*Start the conversion of the calibration offset value */
		  /******************************************************/
					i_APCI3200_ReadCalibrationOffsetValue
						(dev, &ui_DummyValue);
				}	/*  if ((i_CJCFlag == 1) && (i_CalibrationFlag == 0)) */

		 /********************************************************/
				/*Test if the value read is the calibration offset value */
		 /********************************************************/

				if ((i_CalibrationFlag == 1)
					&& (i_CJCFlag == 0)) {
					/* ui_InterruptChannelValue[i_Count + 1]=ui_DigitalTemperature; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 1] =
						ui_DigitalTemperature;

		  /****************************************************/
					/*Start the conversion of the calibration gain value */
		  /****************************************************/
					i_APCI3200_ReadCalibrationGainValue(dev,
						&ui_DummyValue);

				}	/* if ((i_CalibrationFlag == 1) && (i_CJCFlag == 0)) */

	      /******************************************************/
				/*Test if the value read is the calibration gain value */
	      /******************************************************/

				if ((i_CalibrationFlag == 2)
					&& (i_CJCFlag == 0)) {
					/* ui_InterruptChannelValue[i_Count + 2]=ui_DigitalTemperature; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 2] =
						ui_DigitalTemperature;

		  /**********************************************************/
					/*Test if the Calibration channel must be read for the CJC */
		  /**********************************************************/

					/*Test if the polarity is the same */
		  /**********************************/
					/* if(i_CJCPolarity!=i_ADDIDATAPolarity) */
					if (s_BoardInfos[dev->minor].
						i_CJCPolarity !=
						s_BoardInfos[dev->minor].
						i_ADDIDATAPolarity) {
						i_ConvertCJCCalibration = 1;
					}	/* if(i_CJCPolarity!=i_ADDIDATAPolarity) */
					else {
						/* if(i_CJCGain==i_ADDIDATAGain) */
						if (s_BoardInfos[dev->minor].
							i_CJCGain ==
							s_BoardInfos[dev->
								minor].
							i_ADDIDATAGain) {
							i_ConvertCJCCalibration
								= 0;
						}	/* if(i_CJCGain==i_ADDIDATAGain) */
						else {
							i_ConvertCJCCalibration
								= 1;
						}	/* elseif(i_CJCGain==i_ADDIDATAGain) */
					}	/* elseif(i_CJCPolarity!=i_ADDIDATAPolarity) */
					if (i_ConvertCJCCalibration == 1) {
		      /****************************************************************/
						/*Start the conversion of the calibration gain value for the CJC */
		      /****************************************************************/
						i_APCI3200_ReadCJCCalOffset(dev,
							&ui_DummyValue);

					}	/* if(i_ConvertCJCCalibration==1) */
					else {
						/* ui_InterruptChannelValue[i_Count + 4]=0; */
						/* ui_InterruptChannelValue[i_Count + 5]=0; */
						s_BoardInfos[dev->minor].
							ui_InterruptChannelValue
							[s_BoardInfos[dev->
								minor].i_Count +
							4] = 0;
						s_BoardInfos[dev->minor].
							ui_InterruptChannelValue
							[s_BoardInfos[dev->
								minor].i_Count +
							5] = 0;
					}	/* elseif(i_ConvertCJCCalibration==1) */
				}	/* else if ((i_CalibrationFlag == 2) && (i_CJCFlag == 0)) */

		 /********************************************************************/
				/*Test if the value read is the calibration offset value for the CJC */
		 /********************************************************************/

				if ((i_CalibrationFlag == 1)
					&& (i_CJCFlag == 1)) {
					/* ui_InterruptChannelValue[i_Count + 4]=ui_DigitalTemperature; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 4] =
						ui_DigitalTemperature;

		  /****************************************************************/
					/*Start the conversion of the calibration gain value for the CJC */
		  /****************************************************************/
					i_APCI3200_ReadCJCCalGain(dev,
						&ui_DummyValue);

				}	/* if ((i_CalibrationFlag == 1) && (i_CJCFlag == 1)) */

	      /******************************************************************/
				/*Test if the value read is the calibration gain value for the CJC */
	      /******************************************************************/

				if ((i_CalibrationFlag == 2)
					&& (i_CJCFlag == 1)) {
					/* ui_InterruptChannelValue[i_Count + 5]=ui_DigitalTemperature; */
					s_BoardInfos[dev->minor].
						ui_InterruptChannelValue
						[s_BoardInfos[dev->minor].
						i_Count + 5] =
						ui_DigitalTemperature;

					/* if(i_ScanType==1) */
					if (s_BoardInfos[dev->minor].
						i_ScanType == 1) {

						/* i_InterruptFlag=0; */
						s_BoardInfos[dev->minor].
							i_InterruptFlag = 0;
						/* i_Count=i_Count + 6; */
						/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
						/* s_BoardInfos [dev->minor].i_Count=s_BoardInfos [dev->minor].i_Count + 6; */
						s_BoardInfos[dev->minor].
							i_Count =
							s_BoardInfos[dev->
							minor].i_Count + 9;
						/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
					}	/* if(i_ScanType==1) */
					else {
						/* i_Count=0; */
						s_BoardInfos[dev->minor].
							i_Count = 0;
					}	/* elseif(i_ScanType==1) */

					/* if(i_ScanType!=1) */
					if (s_BoardInfos[dev->minor].
						i_ScanType != 1) {
						send_sig(SIGIO, devpriv->tsk_Current, 0);	/*  send signal to the sample */
					}	/* if(i_ScanType!=1) */
					else {
						/* if(i_ChannelCount==i_Sum) */
						if (s_BoardInfos[dev->minor].
							i_ChannelCount ==
							s_BoardInfos[dev->
								minor].i_Sum) {
							send_sig(SIGIO, devpriv->tsk_Current, 0);	/*  send signal to the sample */

						}	/* if(i_ChannelCount==i_Sum) */
					}	/* else if(i_ScanType!=1) */
				}	/* if ((i_CalibrationFlag == 2) && (i_CJCFlag == 1)) */

			}	/* else if ((ui_StatusRegister & 0x2) == 0x2) */
			break;
		}		/* switch(i_ADDIDATAType) */
		break;
	case 2:
	case 3:
		i_APCI3200_InterruptHandleEos(dev);
		break;
	}			/* switch(i_ScanType) */
	return;
}