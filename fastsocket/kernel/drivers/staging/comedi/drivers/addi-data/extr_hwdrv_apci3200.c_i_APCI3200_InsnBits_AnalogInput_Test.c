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
struct comedi_insn {int n; } ;
struct comedi_device {size_t minor; } ;
struct TYPE_4__ {scalar_t__ iobase; } ;
struct TYPE_3__ {scalar_t__ i_Initialised; int i_ChannelNo; int i_InterruptFlag; scalar_t__ i_AutoCalibration; scalar_t__ i_Offset; } ;

/* Variables and functions */
 void* ADDIDATA_DISABLE ; 
 int EINVAL ; 
 scalar_t__ FALSE ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i_APCI3200_Read1AnalogInputChannel (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCalibrationGainValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_ReadCalibrationOffsetValue (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  i_APCI3200_Reset (struct comedi_device*) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* s_BoardInfos ; 

int i_APCI3200_InsnBits_AnalogInput_Test(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_Configuration = 0;
	int i_Temp;		/* ,i_TimeUnit; */
	/* if(i_Initialised==0) */

	if (s_BoardInfos[dev->minor].i_Initialised == 0) {
		i_APCI3200_Reset(dev);
		return -EINVAL;
	}			/* if(i_Initialised==0); */
	if (data[0] != 0 && data[0] != 1) {
		printk("\nError in selection of functionality\n");
		i_APCI3200_Reset(dev);
		return -EINVAL;
	}			/* if(data[0]!=0 && data[0]!=1) */

	if (data[0] == 1)	/* Perform Short Circuit TEST */
	{
      /**************************/
		/*Set the short-cicuit bit */
      /**************************/
		/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
		while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].
						i_Offset + 12) >> 19) & 1) !=
			1) ;
		/* outl((0x00001000 |i_ChannelNo) , devpriv->iobase+i_Offset + 4); */
		outl((0x00001000 | s_BoardInfos[dev->minor].i_ChannelNo),
			devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
			4);
      /*************************/
		/*Set the time unit to ns */
      /*************************/
		/* i_TimeUnit= i_ADDIDATAConversionTimeUnit;
		   i_ADDIDATAConversionTimeUnit= 1; */
		/* i_Temp= i_InterruptFlag ; */
		i_Temp = s_BoardInfos[dev->minor].i_InterruptFlag;
		/* i_InterruptFlag = ADDIDATA_DISABLE; */
		s_BoardInfos[dev->minor].i_InterruptFlag = ADDIDATA_DISABLE;
		i_APCI3200_Read1AnalogInputChannel(dev, s, insn, data);
		/* if(i_AutoCalibration == FALSE) */
		if (s_BoardInfos[dev->minor].i_AutoCalibration == FALSE) {
			/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
			while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].
							i_Offset +
							12) >> 19) & 1) != 1) ;

			/* outl((0x00001000 |i_ChannelNo) , devpriv->iobase+i_Offset + 4); */
			outl((0x00001000 | s_BoardInfos[dev->minor].
					i_ChannelNo),
				devpriv->iobase +
				s_BoardInfos[dev->minor].i_Offset + 4);
			data++;
			i_APCI3200_ReadCalibrationOffsetValue(dev, data);
			data++;
			i_APCI3200_ReadCalibrationGainValue(dev, data);
		}
	} else {
		/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
		while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].
						i_Offset + 12) >> 19) & 1) !=
			1) ;
		/* outl((0x00000800|i_ChannelNo) , devpriv->iobase+i_Offset + 4); */
		outl((0x00000800 | s_BoardInfos[dev->minor].i_ChannelNo),
			devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
			4);
		/* ui_Configuration = inl(devpriv->iobase+i_Offset + 0); */
		ui_Configuration =
			inl(devpriv->iobase +
			s_BoardInfos[dev->minor].i_Offset + 0);
      /*************************/
		/*Set the time unit to ns */
      /*************************/
		/* i_TimeUnit= i_ADDIDATAConversionTimeUnit;
		   i_ADDIDATAConversionTimeUnit= 1; */
		/* i_Temp= i_InterruptFlag ; */
		i_Temp = s_BoardInfos[dev->minor].i_InterruptFlag;
		/* i_InterruptFlag = ADDIDATA_DISABLE; */
		s_BoardInfos[dev->minor].i_InterruptFlag = ADDIDATA_DISABLE;
		i_APCI3200_Read1AnalogInputChannel(dev, s, insn, data);
		/* if(i_AutoCalibration == FALSE) */
		if (s_BoardInfos[dev->minor].i_AutoCalibration == FALSE) {
			/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
			while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].
							i_Offset +
							12) >> 19) & 1) != 1) ;
			/* outl((0x00000800|i_ChannelNo) , devpriv->iobase+i_Offset + 4); */
			outl((0x00000800 | s_BoardInfos[dev->minor].
					i_ChannelNo),
				devpriv->iobase +
				s_BoardInfos[dev->minor].i_Offset + 4);
			data++;
			i_APCI3200_ReadCalibrationOffsetValue(dev, data);
			data++;
			i_APCI3200_ReadCalibrationGainValue(dev, data);
		}
	}
	/* i_InterruptFlag=i_Temp ; */
	s_BoardInfos[dev->minor].i_InterruptFlag = i_Temp;
	/* printk("\ni_InterruptFlag=%d\n",i_InterruptFlag); */
	return insn->n;
}