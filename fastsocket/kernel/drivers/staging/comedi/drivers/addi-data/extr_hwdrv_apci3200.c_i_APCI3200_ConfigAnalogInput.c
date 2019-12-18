#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; scalar_t__* unused; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {size_t minor; } ;
struct TYPE_7__ {int iobase; int /*<<< orphan*/  tsk_Current; int /*<<< orphan*/  i_IobaseAmcc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * w_GainValue; int /*<<< orphan*/ * ul_GainFactor; int /*<<< orphan*/ * ul_CurrentSource; int /*<<< orphan*/  ul_CurrentSourceCJC; } ;
struct TYPE_5__ {int b_StructInitialized; int i_CJCAvailable; int i_CJCGain; int i_InterruptFlag; unsigned int i_ChannelCount; unsigned int ui_Channel_num; int i_Initialised; unsigned int i_ConnectionType; unsigned int i_ScanType; unsigned int i_ADDIDATAPolarity; unsigned int i_ADDIDATAGain; unsigned int i_ADDIDATAConversionTime; unsigned int i_ADDIDATAConversionTimeUnit; unsigned int i_ADDIDATAType; unsigned int i_ChannelNo; int i_Offset; scalar_t__ i_Sum; scalar_t__ i_Count; TYPE_3__* ui_ScanValueArray; TYPE_3__* s_Module; scalar_t__ i_AutoCalibration; scalar_t__ i_CJCPolarity; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MAX_MODULE ; 
 int /*<<< orphan*/  current ; 
 TYPE_4__* devpriv ; 
 int /*<<< orphan*/  i_APCI3200_ReadAnalogInput (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_Reset (struct comedi_device*) ; 
 int inl (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outl (unsigned int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* s_BoardInfos ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  v_GetAPCI3200EepromCalibrationValue (int /*<<< orphan*/ ,TYPE_1__*) ; 

int i_APCI3200_ConfigAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{

	unsigned int ul_Config = 0, ul_Temp = 0;
	unsigned int ui_ChannelNo = 0;
	unsigned int ui_Dummy = 0;
	int i_err = 0;

	/* Begin JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

#ifdef PRINT_INFO
	int i = 0, i2 = 0;
#endif
	/* End JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/*  Initialize the structure */
	if (s_BoardInfos[dev->minor].b_StructInitialized != 1) {
		s_BoardInfos[dev->minor].i_CJCAvailable = 1;
		s_BoardInfos[dev->minor].i_CJCPolarity = 0;
		s_BoardInfos[dev->minor].i_CJCGain = 2;	/* changed from 0 to 2 */
		s_BoardInfos[dev->minor].i_InterruptFlag = 0;
		s_BoardInfos[dev->minor].i_AutoCalibration = 0;	/* : auto calibration */
		s_BoardInfos[dev->minor].i_ChannelCount = 0;
		s_BoardInfos[dev->minor].i_Sum = 0;
		s_BoardInfos[dev->minor].ui_Channel_num = 0;
		s_BoardInfos[dev->minor].i_Count = 0;
		s_BoardInfos[dev->minor].i_Initialised = 0;
		s_BoardInfos[dev->minor].b_StructInitialized = 1;

		/* Begin JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
		s_BoardInfos[dev->minor].i_ConnectionType = 0;
		/* End JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

		/* Begin JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
		memset(s_BoardInfos[dev->minor].s_Module, 0,
			sizeof(s_BoardInfos[dev->minor].s_Module[MAX_MODULE]));

		v_GetAPCI3200EepromCalibrationValue(devpriv->i_IobaseAmcc,
			&s_BoardInfos[dev->minor]);

#ifdef PRINT_INFO
		for (i = 0; i < MAX_MODULE; i++) {
			printk("\n s_Module[%i].ul_CurrentSourceCJC = %lu", i,
				s_BoardInfos[dev->minor].s_Module[i].
				ul_CurrentSourceCJC);

			for (i2 = 0; i2 < 5; i2++) {
				printk("\n s_Module[%i].ul_CurrentSource [%i] = %lu", i, i2, s_BoardInfos[dev->minor].s_Module[i].ul_CurrentSource[i2]);
			}

			for (i2 = 0; i2 < 8; i2++) {
				printk("\n s_Module[%i].ul_GainFactor [%i] = %lu", i, i2, s_BoardInfos[dev->minor].s_Module[i].ul_GainFactor[i2]);
			}

			for (i2 = 0; i2 < 8; i2++) {
				printk("\n s_Module[%i].w_GainValue [%i] = %u",
					i, i2,
					s_BoardInfos[dev->minor].s_Module[i].
					w_GainValue[i2]);
			}
		}
#endif
		/* End JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */
	}

	if (data[0] != 0 && data[0] != 1 && data[0] != 2) {
		printk("\nThe selection of acquisition type is in error\n");
		i_err++;
	}			/* if(data[0]!=0 && data[0]!=1 && data[0]!=2) */
	if (data[0] == 1) {
		if (data[14] != 0 && data[14] != 1 && data[14] != 2
			&& data[14] != 4) {
			printk("\n Error in selection of RTD connection type\n");
			i_err++;
		}		/* if(data[14]!=0 && data[14]!=1 && data[14]!=2 && data[14]!=4) */
	}			/* if(data[0]==1 ) */
	if (data[1] < 0 || data[1] > 7) {
		printk("\nThe selection of gain is in error\n");
		i_err++;
	}			/*  if(data[1]<0 || data[1]>7) */
	if (data[2] != 0 && data[2] != 1) {
		printk("\nThe selection of polarity is in error\n");
		i_err++;
	}			/* if(data[2]!=0 &&  data[2]!=1) */
	if (data[3] != 0) {
		printk("\nThe selection of offset range  is in error\n");
		i_err++;
	}			/*  if(data[3]!=0) */
	if (data[4] != 0 && data[4] != 1) {
		printk("\nThe selection of coupling is in error\n");
		i_err++;
	}			/* if(data[4]!=0 &&  data[4]!=1) */
	if (data[5] != 0 && data[5] != 1) {
		printk("\nThe selection of single/differential mode is in error\n");
		i_err++;
	}			/* if(data[5]!=0 &&  data[5]!=1) */
	if (data[8] != 0 && data[8] != 1 && data[2] != 2) {
		printk("\nError in selection of functionality\n");
	}			/* if(data[8]!=0 && data[8]!=1 && data[2]!=2) */
	if (data[12] == 0 || data[12] == 1) {
		if (data[6] != 20 && data[6] != 40 && data[6] != 80
			&& data[6] != 160) {
			printk("\nThe selection of conversion time reload value is in error\n");
			i_err++;
		}		/*  if (data[6]!=20 && data[6]!=40 && data[6]!=80 && data[6]!=160 ) */
		if (data[7] != 2) {
			printk("\nThe selection of conversion time unit  is in error\n");
			i_err++;
		}		/*  if(data[7]!=2) */
	}
	if (data[9] != 0 && data[9] != 1) {
		printk("\nThe selection of interrupt enable is in error\n");
		i_err++;
	}			/* if(data[9]!=0 &&  data[9]!=1) */
	if (data[11] < 0 || data[11] > 4) {
		printk("\nThe selection of module is in error\n");
		i_err++;
	}			/* if(data[11] <0 ||  data[11]>1) */
	if (data[12] < 0 || data[12] > 3) {
		printk("\nThe selection of singlechannel/scan selection is in error\n");
		i_err++;
	}			/* if(data[12] < 0 ||  data[12]> 3) */
	if (data[13] < 0 || data[13] > 16) {
		printk("\nThe selection of number of channels is in error\n");
		i_err++;
	}			/*  if(data[13] <0 ||data[13] >15) */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/*
	   i_ChannelCount=data[13];
	   i_ScanType=data[12];
	   i_ADDIDATAPolarity = data[2];
	   i_ADDIDATAGain=data[1];
	   i_ADDIDATAConversionTime=data[6];
	   i_ADDIDATAConversionTimeUnit=data[7];
	   i_ADDIDATAType=data[0];
	 */

	/*  Save acquisition configuration for the actual board */
	s_BoardInfos[dev->minor].i_ChannelCount = data[13];
	s_BoardInfos[dev->minor].i_ScanType = data[12];
	s_BoardInfos[dev->minor].i_ADDIDATAPolarity = data[2];
	s_BoardInfos[dev->minor].i_ADDIDATAGain = data[1];
	s_BoardInfos[dev->minor].i_ADDIDATAConversionTime = data[6];
	s_BoardInfos[dev->minor].i_ADDIDATAConversionTimeUnit = data[7];
	s_BoardInfos[dev->minor].i_ADDIDATAType = data[0];
	/* Begin JK 19.10.2004: APCI-3200 Driver update 0.7.57 -> 0.7.68 */
	s_BoardInfos[dev->minor].i_ConnectionType = data[5];
	/* End JK 19.10.2004: APCI-3200 Driver update 0.7.57 -> 0.7.68 */
	/* END JK 06.07.04: Management of sevrals boards */

	/* Begin JK 19.10.2004: APCI-3200 Driver update 0.7.57 -> 0.7.68 */
	memset(s_BoardInfos[dev->minor].ui_ScanValueArray, 0, (7 + 12) * sizeof(unsigned int));	/*  7 is the maximal number of channels */
	/* End JK 19.10.2004: APCI-3200 Driver update 0.7.57 -> 0.7.68 */

	/* BEGIN JK 02.07.04 : This while can't be do, it block the process when using severals boards */
	/* while(i_InterruptFlag==1) */
	while (s_BoardInfos[dev->minor].i_InterruptFlag == 1) {
#ifndef MSXBOX
		udelay(1);
#else
		/*  In the case where the driver is compiled for the MSX-Box */
		/*  we used a printk to have a little delay because udelay */
		/*  seems to be broken under the MSX-Box. */
		/*  This solution hat to be studied. */
		printk("");
#endif
	}
	/* END JK 02.07.04 : This while can't be do, it block the process when using severals boards */

	ui_ChannelNo = CR_CHAN(insn->chanspec);	/*  get the channel */
	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* i_ChannelNo=ui_ChannelNo; */
	/* ui_Channel_num =ui_ChannelNo; */

	s_BoardInfos[dev->minor].i_ChannelNo = ui_ChannelNo;
	s_BoardInfos[dev->minor].ui_Channel_num = ui_ChannelNo;

	/* END JK 06.07.04: Management of sevrals boards */

	if (data[5] == 0) {
		if (ui_ChannelNo < 0 || ui_ChannelNo > 15) {
			printk("\nThe Selection of the channel is in error\n");
			i_err++;
		}		/*  if(ui_ChannelNo<0 || ui_ChannelNo>15) */
	}			/* if(data[5]==0) */
	else {
		if (data[14] == 2) {
			if (ui_ChannelNo < 0 || ui_ChannelNo > 3) {
				printk("\nThe Selection of the channel is in error\n");
				i_err++;
			}	/*  if(ui_ChannelNo<0 || ui_ChannelNo>3) */
		}		/* if(data[14]==2) */
		else {
			if (ui_ChannelNo < 0 || ui_ChannelNo > 7) {
				printk("\nThe Selection of the channel is in error\n");
				i_err++;
			}	/*  if(ui_ChannelNo<0 || ui_ChannelNo>7) */
		}		/* elseif(data[14]==2) */
	}			/* elseif(data[5]==0) */
	if (data[12] == 0 || data[12] == 1) {
		switch (data[5]) {
		case 0:
			if (ui_ChannelNo >= 0 && ui_ChannelNo <= 3) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_Offset=0; */
				s_BoardInfos[dev->minor].i_Offset = 0;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* if(ui_ChannelNo >=0 && ui_ChannelNo <=3) */
			if (ui_ChannelNo >= 4 && ui_ChannelNo <= 7) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_Offset=64; */
				s_BoardInfos[dev->minor].i_Offset = 64;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* if(ui_ChannelNo >=4 && ui_ChannelNo <=7) */
			if (ui_ChannelNo >= 8 && ui_ChannelNo <= 11) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_Offset=128; */
				s_BoardInfos[dev->minor].i_Offset = 128;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* if(ui_ChannelNo >=8 && ui_ChannelNo <=11) */
			if (ui_ChannelNo >= 12 && ui_ChannelNo <= 15) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_Offset=192; */
				s_BoardInfos[dev->minor].i_Offset = 192;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* if(ui_ChannelNo >=12 && ui_ChannelNo <=15) */
			break;
		case 1:
			if (data[14] == 2) {
				if (ui_ChannelNo == 0) {
					/* BEGIN JK 06.07.04: Management of sevrals boards */
					/* i_Offset=0; */
					s_BoardInfos[dev->minor].i_Offset = 0;
					/* END JK 06.07.04: Management of sevrals boards */
				}	/* if(ui_ChannelNo ==0 ) */
				if (ui_ChannelNo == 1) {
					/* BEGIN JK 06.07.04: Management of sevrals boards */
					/* i_Offset=0; */
					s_BoardInfos[dev->minor].i_Offset = 64;
					/* END JK 06.07.04: Management of sevrals boards */
				}	/*  if(ui_ChannelNo ==1) */
				if (ui_ChannelNo == 2) {
					/* BEGIN JK 06.07.04: Management of sevrals boards */
					/* i_Offset=128; */
					s_BoardInfos[dev->minor].i_Offset = 128;
					/* END JK 06.07.04: Management of sevrals boards */
				}	/* if(ui_ChannelNo ==2 ) */
				if (ui_ChannelNo == 3) {
					/* BEGIN JK 06.07.04: Management of sevrals boards */
					/* i_Offset=192; */
					s_BoardInfos[dev->minor].i_Offset = 192;
					/* END JK 06.07.04: Management of sevrals boards */
				}	/* if(ui_ChannelNo ==3) */

				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_ChannelNo=0; */
				s_BoardInfos[dev->minor].i_ChannelNo = 0;
				/* END JK 06.07.04: Management of sevrals boards */
				ui_ChannelNo = 0;
				break;
			}	/* if(data[14]==2) */
			if (ui_ChannelNo >= 0 && ui_ChannelNo <= 1) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_Offset=0; */
				s_BoardInfos[dev->minor].i_Offset = 0;
				/* END JK 06.07.04: Management of sevrals boards */
			}	/* if(ui_ChannelNo >=0 && ui_ChannelNo <=1) */
			if (ui_ChannelNo >= 2 && ui_ChannelNo <= 3) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_ChannelNo=i_ChannelNo-2; */
				/* i_Offset=64; */
				s_BoardInfos[dev->minor].i_ChannelNo =
					s_BoardInfos[dev->minor].i_ChannelNo -
					2;
				s_BoardInfos[dev->minor].i_Offset = 64;
				/* END JK 06.07.04: Management of sevrals boards */
				ui_ChannelNo = ui_ChannelNo - 2;
			}	/* if(ui_ChannelNo >=2 && ui_ChannelNo <=3) */
			if (ui_ChannelNo >= 4 && ui_ChannelNo <= 5) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_ChannelNo=i_ChannelNo-4; */
				/* i_Offset=128; */
				s_BoardInfos[dev->minor].i_ChannelNo =
					s_BoardInfos[dev->minor].i_ChannelNo -
					4;
				s_BoardInfos[dev->minor].i_Offset = 128;
				/* END JK 06.07.04: Management of sevrals boards */
				ui_ChannelNo = ui_ChannelNo - 4;
			}	/* if(ui_ChannelNo >=4 && ui_ChannelNo <=5) */
			if (ui_ChannelNo >= 6 && ui_ChannelNo <= 7) {
				/* BEGIN JK 06.07.04: Management of sevrals boards */
				/* i_ChannelNo=i_ChannelNo-6; */
				/* i_Offset=192; */
				s_BoardInfos[dev->minor].i_ChannelNo =
					s_BoardInfos[dev->minor].i_ChannelNo -
					6;
				s_BoardInfos[dev->minor].i_Offset = 192;
				/* END JK 06.07.04: Management of sevrals boards */
				ui_ChannelNo = ui_ChannelNo - 6;
			}	/* if(ui_ChannelNo >=6 && ui_ChannelNo <=7) */
			break;

		default:
			printk("\n This selection of polarity does not exist\n");
			i_err++;
		}		/* switch(data[2]) */
	}			/* if(data[12]==0 || data[12]==1) */
	else {
		switch (data[11]) {
		case 1:
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* i_Offset=0; */
			s_BoardInfos[dev->minor].i_Offset = 0;
			/* END JK 06.07.04: Management of sevrals boards */
			break;
		case 2:
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* i_Offset=64; */
			s_BoardInfos[dev->minor].i_Offset = 64;
			/* END JK 06.07.04: Management of sevrals boards */
			break;
		case 3:
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* i_Offset=128; */
			s_BoardInfos[dev->minor].i_Offset = 128;
			/* END JK 06.07.04: Management of sevrals boards */
			break;
		case 4:
			/* BEGIN JK 06.07.04: Management of sevrals boards */
			/* i_Offset=192; */
			s_BoardInfos[dev->minor].i_Offset = 192;
			/* END JK 06.07.04: Management of sevrals boards */
			break;
		default:
			printk("\nError in module selection\n");
			i_err++;
		}		/*  switch(data[11]) */
	}			/*  elseif(data[12]==0 || data[12]==1) */
	if (i_err) {
		i_APCI3200_Reset(dev);
		return -EINVAL;
	}
	/* if(i_ScanType!=1) */
	if (s_BoardInfos[dev->minor].i_ScanType != 1) {
		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* i_Count=0; */
		/* i_Sum=0; */
		s_BoardInfos[dev->minor].i_Count = 0;
		s_BoardInfos[dev->minor].i_Sum = 0;
		/* END JK 06.07.04: Management of sevrals boards */
	}			/* if(i_ScanType!=1) */

	ul_Config =
		data[1] | (data[2] << 6) | (data[5] << 7) | (data[3] << 8) |
		(data[4] << 9);
	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* END JK 06.07.04: Management of sevrals boards */
  /*********************************/
	/* Write the channel to configure */
  /*********************************/
	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* outl(0 | ui_ChannelNo , devpriv->iobase+i_Offset + 0x4); */
	outl(0 | ui_ChannelNo,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 0x4);
	/* END JK 06.07.04: Management of sevrals boards */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* END JK 06.07.04: Management of sevrals boards */
  /**************************/
	/* Reset the configuration */
  /**************************/
	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* outl(0 , devpriv->iobase+i_Offset + 0x0); */
	outl(0, devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 0x0);
	/* END JK 06.07.04: Management of sevrals boards */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* END JK 06.07.04: Management of sevrals boards */

  /***************************/
	/* Write the configuration */
  /***************************/
	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* outl(ul_Config , devpriv->iobase+i_Offset + 0x0); */
	outl(ul_Config,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 0x0);
	/* END JK 06.07.04: Management of sevrals boards */

  /***************************/
	/*Reset the calibration bit */
  /***************************/
	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* ul_Temp = inl(devpriv->iobase+i_Offset + 12); */
	ul_Temp = inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 12);
	/* END JK 06.07.04: Management of sevrals boards */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* END JK 06.07.04: Management of sevrals boards */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* outl((ul_Temp & 0xFFF9FFFF) , devpriv->iobase+.i_Offset + 12); */
	outl((ul_Temp & 0xFFF9FFFF),
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 12);
	/* END JK 06.07.04: Management of sevrals boards */

	if (data[9] == 1) {
		devpriv->tsk_Current = current;
		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* i_InterruptFlag=1; */
		s_BoardInfos[dev->minor].i_InterruptFlag = 1;
		/* END JK 06.07.04: Management of sevrals boards */
	}			/*  if(data[9]==1) */
	else {
		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* i_InterruptFlag=0; */
		s_BoardInfos[dev->minor].i_InterruptFlag = 0;
		/* END JK 06.07.04: Management of sevrals boards */
	}			/* else  if(data[9]==1) */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* i_Initialised=1; */
	s_BoardInfos[dev->minor].i_Initialised = 1;
	/* END JK 06.07.04: Management of sevrals boards */

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* if(i_ScanType==1) */
	if (s_BoardInfos[dev->minor].i_ScanType == 1)
		/* END JK 06.07.04: Management of sevrals boards */
	{
		/* BEGIN JK 06.07.04: Management of sevrals boards */
		/* i_Sum=i_Sum+1; */
		s_BoardInfos[dev->minor].i_Sum =
			s_BoardInfos[dev->minor].i_Sum + 1;
		/* END JK 06.07.04: Management of sevrals boards */

		insn->unused[0] = 0;
		i_APCI3200_ReadAnalogInput(dev, s, insn, &ui_Dummy);
	}

	return insn->n;
}