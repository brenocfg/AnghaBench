#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int* unused; int n; } ;
struct comedi_device {size_t minor; } ;
struct TYPE_2__ {scalar_t__ i_Initialised; unsigned int* ui_InterruptChannelValue; size_t i_Count; int i_ADDIDATAType; int i_InterruptFlag; int i_CJCAvailable; int i_AutoCalibration; int i_ScanType; int /*<<< orphan*/  i_Sum; int /*<<< orphan*/  ui_Channel_num; int /*<<< orphan*/  i_ADDIDATAGain; int /*<<< orphan*/  i_CJCGain; int /*<<< orphan*/  i_ADDIDATAPolarity; int /*<<< orphan*/  i_CJCPolarity; } ;

/* Variables and functions */
 int EINVAL ; 
 int FALSE ; 
 int /*<<< orphan*/  i_APCI3200_GetChannelCalibrationValue (struct comedi_device*,int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_Read1AnalogInputChannel (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCJCCalGain (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCJCCalOffset (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCJCValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCalibrationGainValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCalibrationOffsetValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_Reset (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* s_BoardInfos ; 

int i_APCI3200_ReadAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_DummyValue = 0;
	int i_ConvertCJCCalibration;
	int i = 0;

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* if(i_Initialised==0) */
	if (s_BoardInfos[dev->minor].i_Initialised == 0)
		/* END JK 06.07.04: Management of sevrals boards */
	{
		i_APCI3200_Reset(dev);
		return -EINVAL;
	}			/* if(i_Initialised==0); */

#ifdef PRINT_INFO
	printk("\n insn->unused[0] = %i", insn->unused[0]);
#endif

	switch (insn->unused[0]) {
	case 0:

		i_APCI3200_Read1AnalogInputChannel(dev, s, insn,
			&ui_DummyValue);
		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* ui_InterruptChannelValue[i_Count+0]=ui_DummyValue; */
		s_BoardInfos[dev->minor].
			ui_InterruptChannelValue[s_BoardInfos[dev->minor].
			i_Count + 0] = ui_DummyValue;
		/* END JK 06.07.04: Management of sevrals boards */

		/* Begin JK 25.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
		i_APCI3200_GetChannelCalibrationValue(dev,
			s_BoardInfos[dev->minor].ui_Channel_num,
			&s_BoardInfos[dev->minor].
			ui_InterruptChannelValue[s_BoardInfos[dev->minor].
				i_Count + 6],
			&s_BoardInfos[dev->minor].
			ui_InterruptChannelValue[s_BoardInfos[dev->minor].
				i_Count + 7],
			&s_BoardInfos[dev->minor].
			ui_InterruptChannelValue[s_BoardInfos[dev->minor].
				i_Count + 8]);

#ifdef PRINT_INFO
		printk("\n s_BoardInfos [dev->minor].ui_InterruptChannelValue[s_BoardInfos [dev->minor].i_Count+6] = %lu", s_BoardInfos[dev->minor].ui_InterruptChannelValue[s_BoardInfos[dev->minor].i_Count + 6]);

		printk("\n s_BoardInfos [dev->minor].ui_InterruptChannelValue[s_BoardInfos [dev->minor].i_Count+7] = %lu", s_BoardInfos[dev->minor].ui_InterruptChannelValue[s_BoardInfos[dev->minor].i_Count + 7]);

		printk("\n s_BoardInfos [dev->minor].ui_InterruptChannelValue[s_BoardInfos [dev->minor].i_Count+8] = %lu", s_BoardInfos[dev->minor].ui_InterruptChannelValue[s_BoardInfos[dev->minor].i_Count + 8]);
#endif

		/* End JK 25.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* if((i_ADDIDATAType==2) && (i_InterruptFlag == FALSE) && (i_CJCAvailable==1)) */
		if ((s_BoardInfos[dev->minor].i_ADDIDATAType == 2)
			&& (s_BoardInfos[dev->minor].i_InterruptFlag == FALSE)
			&& (s_BoardInfos[dev->minor].i_CJCAvailable == 1))
			/* END JK 06.07.04: Management of sevrals boards */
		{
			i_APCI3200_ReadCJCValue(dev, &ui_DummyValue);
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* ui_InterruptChannelValue[i_Count + 3]=ui_DummyValue; */
			s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[s_BoardInfos[dev->
					minor].i_Count + 3] = ui_DummyValue;
			/* END JK 06.07.04: Management of sevrals boards */
		}		/* if((i_ADDIDATAType==2) && (i_InterruptFlag == FALSE)) */
		else {
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* ui_InterruptChannelValue[i_Count + 3]=0; */
			s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[s_BoardInfos[dev->
					minor].i_Count + 3] = 0;
			/* END JK 06.07.04: Management of sevrals boards */
		}		/* elseif((i_ADDIDATAType==2) && (i_InterruptFlag == FALSE) && (i_CJCAvailable==1)) */

		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* if (( i_AutoCalibration == FALSE) && (i_InterruptFlag == FALSE)) */
		if ((s_BoardInfos[dev->minor].i_AutoCalibration == FALSE)
			&& (s_BoardInfos[dev->minor].i_InterruptFlag == FALSE))
			/* END JK 06.07.04: Management of sevrals boards */
		{
			i_APCI3200_ReadCalibrationOffsetValue(dev,
				&ui_DummyValue);
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* ui_InterruptChannelValue[i_Count + 1]=ui_DummyValue; */
			s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[s_BoardInfos[dev->
					minor].i_Count + 1] = ui_DummyValue;
			/* END JK 06.07.04: Management of sevrals boards */
			i_APCI3200_ReadCalibrationGainValue(dev,
				&ui_DummyValue);
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* ui_InterruptChannelValue[i_Count + 2]=ui_DummyValue; */
			s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[s_BoardInfos[dev->
					minor].i_Count + 2] = ui_DummyValue;
			/* END JK 06.07.04: Management of sevrals boards */
		}		/* if (( i_AutoCalibration == FALSE) && (i_InterruptFlag == FALSE)) */

		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* if((i_ADDIDATAType==2) && (i_InterruptFlag == FALSE)&& (i_CJCAvailable==1)) */
		if ((s_BoardInfos[dev->minor].i_ADDIDATAType == 2)
			&& (s_BoardInfos[dev->minor].i_InterruptFlag == FALSE)
			&& (s_BoardInfos[dev->minor].i_CJCAvailable == 1))
			/* END JK 06.07.04: Management of sevrals boards */
		{
	  /**********************************************************/
			/*Test if the Calibration channel must be read for the CJC */
	  /**********************************************************/
	  /**********************************/
			/*Test if the polarity is the same */
	  /**********************************/
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* if(i_CJCPolarity!=i_ADDIDATAPolarity) */
			if (s_BoardInfos[dev->minor].i_CJCPolarity !=
				s_BoardInfos[dev->minor].i_ADDIDATAPolarity)
				/* END JK 06.07.04: Management of sevrals boards */
			{
				i_ConvertCJCCalibration = 1;
			}	/* if(i_CJCPolarity!=i_ADDIDATAPolarity) */
			else {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* if(i_CJCGain==i_ADDIDATAGain) */
				if (s_BoardInfos[dev->minor].i_CJCGain ==
					s_BoardInfos[dev->minor].i_ADDIDATAGain)
					/* END JK 06.07.04: Management of sevrals boards */
				{
					i_ConvertCJCCalibration = 0;
				}	/* if(i_CJCGain==i_ADDIDATAGain) */
				else {
					i_ConvertCJCCalibration = 1;
				}	/* elseif(i_CJCGain==i_ADDIDATAGain) */
			}	/* elseif(i_CJCPolarity!=i_ADDIDATAPolarity) */
			if (i_ConvertCJCCalibration == 1) {
				i_APCI3200_ReadCJCCalOffset(dev,
					&ui_DummyValue);
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* ui_InterruptChannelValue[i_Count+4]=ui_DummyValue; */
				s_BoardInfos[dev->minor].
					ui_InterruptChannelValue[s_BoardInfos
					[dev->minor].i_Count + 4] =
					ui_DummyValue;
				/* END JK 06.07.04: Management of sevrals boards */

				i_APCI3200_ReadCJCCalGain(dev, &ui_DummyValue);

				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* ui_InterruptChannelValue[i_Count+5]=ui_DummyValue; */
				s_BoardInfos[dev->minor].
					ui_InterruptChannelValue[s_BoardInfos
					[dev->minor].i_Count + 5] =
					ui_DummyValue;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* if(i_ConvertCJCCalibration==1) */
			else {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* ui_InterruptChannelValue[i_Count+4]=0; */
				/* ui_InterruptChannelValue[i_Count+5]=0; */

				s_BoardInfos[dev->minor].
					ui_InterruptChannelValue[s_BoardInfos
					[dev->minor].i_Count + 4] = 0;
				s_BoardInfos[dev->minor].
					ui_InterruptChannelValue[s_BoardInfos
					[dev->minor].i_Count + 5] = 0;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* elseif(i_ConvertCJCCalibration==1) */
		}		/* if((i_ADDIDATAType==2) && (i_InterruptFlag == FALSE)) */

		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* if(i_ScanType!=1) */
		if (s_BoardInfos[dev->minor].i_ScanType != 1) {
			/* i_Count=0; */
			s_BoardInfos[dev->minor].i_Count = 0;
		}		/* if(i_ScanType!=1) */
		else {
			/* i_Count=i_Count +6; */
			/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
			/* s_BoardInfos [dev->minor].i_Count=s_BoardInfos [dev->minor].i_Count +6; */
			s_BoardInfos[dev->minor].i_Count =
				s_BoardInfos[dev->minor].i_Count + 9;
			/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
		}		/* else if(i_ScanType!=1) */

		/* if((i_ScanType==1) &&(i_InterruptFlag==1)) */
		if ((s_BoardInfos[dev->minor].i_ScanType == 1)
			&& (s_BoardInfos[dev->minor].i_InterruptFlag == 1)) {
			/* i_Count=i_Count-6; */
			/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
			/* s_BoardInfos [dev->minor].i_Count=s_BoardInfos [dev->minor].i_Count-6; */
			s_BoardInfos[dev->minor].i_Count =
				s_BoardInfos[dev->minor].i_Count - 9;
			/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
		}
		/* if(i_ScanType==0) */
		if (s_BoardInfos[dev->minor].i_ScanType == 0) {
			/*
			   data[0]= ui_InterruptChannelValue[0];
			   data[1]= ui_InterruptChannelValue[1];
			   data[2]= ui_InterruptChannelValue[2];
			   data[3]= ui_InterruptChannelValue[3];
			   data[4]= ui_InterruptChannelValue[4];
			   data[5]= ui_InterruptChannelValue[5];
			 */
#ifdef PRINT_INFO
			printk("\n data[0]= s_BoardInfos [dev->minor].ui_InterruptChannelValue[0];");
#endif
			data[0] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[0];
			data[1] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[1];
			data[2] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[2];
			data[3] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[3];
			data[4] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[4];
			data[5] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[5];

			/* Begin JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
			/* printk("\n 0 - i_APCI3200_GetChannelCalibrationValue data [6] = %lu, data [7] = %lu, data [8] = %lu", data [6], data [7], data [8]); */
			i_APCI3200_GetChannelCalibrationValue(dev,
				s_BoardInfos[dev->minor].ui_Channel_num,
				&data[6], &data[7], &data[8]);
			/* End JK 22.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
		}
		break;
	case 1:

		for (i = 0; i < insn->n; i++) {
			/* data[i]=ui_InterruptChannelValue[i]; */
			data[i] =
				s_BoardInfos[dev->minor].
				ui_InterruptChannelValue[i];
		}

		/* i_Count=0; */
		/* i_Sum=0; */
		/* if(i_ScanType==1) */
		s_BoardInfos[dev->minor].i_Count = 0;
		s_BoardInfos[dev->minor].i_Sum = 0;
		if (s_BoardInfos[dev->minor].i_ScanType == 1) {
			/* i_Initialised=0; */
			/* i_InterruptFlag=0; */
			s_BoardInfos[dev->minor].i_Initialised = 0;
			s_BoardInfos[dev->minor].i_InterruptFlag = 0;
			/* END JK 06.07.04: Management of sevrals boards */
		}
		break;
	default:
		printk("\nThe parameters passed are in error\n");
		i_APCI3200_Reset(dev);
		return -EINVAL;
	}			/* switch(insn->unused[0]) */

	return insn->n;
}