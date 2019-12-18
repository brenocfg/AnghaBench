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
struct TYPE_4__ {scalar_t__ iobase; } ;
struct TYPE_3__ {int i_ADDIDATAConversionTimeUnit; int i_ADDIDATAConversionTime; scalar_t__ i_InterruptFlag; scalar_t__ i_Offset; } ;

/* Variables and functions */
 scalar_t__ ADDIDATA_DISABLE ; 
 scalar_t__ ADDIDATA_ENABLE ; 
 TYPE_2__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 TYPE_1__* s_BoardInfos ; 

int i_APCI3200_ReadCJCCalGain(struct comedi_device *dev, unsigned int *data)
{
	unsigned int ui_EOC = 0;
	int ui_CommandRegister = 0;
  /*******************************/
	/* Set the convert timing unit */
  /*******************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(i_ADDIDATAConversionTimeUnit , devpriv->iobase+i_Offset + 36); */
	outl(s_BoardInfos[dev->minor].i_ADDIDATAConversionTimeUnit,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 36);
  /**************************/
	/* Set the convert timing */
  /**************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(i_ADDIDATAConversionTime , devpriv->iobase+i_Offset + 32); */
	outl(s_BoardInfos[dev->minor].i_ADDIDATAConversionTime,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 32);
  /******************************/
	/*Configure the CJC Conversion */
  /******************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(0x00000400,devpriv->iobase+i_Offset + 4); */
	outl(0x00000400,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 4);
  /*******************************/
	/*Configure the Gain Conversion */
  /*******************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(0x00040000,devpriv->iobase+i_Offset + 12); */
	outl(0x00040000,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 12);

  /*******************************/
	/*Initialise dw_CommandRegister */
  /*******************************/
	ui_CommandRegister = 0;
  /*********************************/
	/*Test if the interrupt is enable */
  /*********************************/
	/* if (i_InterruptFlag == ADDIDATA_ENABLE) */
	if (s_BoardInfos[dev->minor].i_InterruptFlag == ADDIDATA_ENABLE) {
      /**********************/
		/*Enable the interrupt */
      /**********************/
		ui_CommandRegister = ui_CommandRegister | 0x00100000;
	}
  /**********************/
	/*Start the conversion */
  /**********************/
	ui_CommandRegister = ui_CommandRegister | 0x00080000;
  /***************************/
	/*Write the command regiter */
  /***************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(ui_CommandRegister ,devpriv->iobase+i_Offset + 8); */
	outl(ui_CommandRegister,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 8);
	/* if (i_InterruptFlag == ADDIDATA_DISABLE) */
	if (s_BoardInfos[dev->minor].i_InterruptFlag == ADDIDATA_DISABLE) {
		do {
	  /*******************/
			/*Read the EOC flag */
	  /*******************/
			/* ui_EOC = inl(devpriv->iobase+i_Offset + 20) & 1; */
			ui_EOC = inl(devpriv->iobase +
				s_BoardInfos[dev->minor].i_Offset + 20) & 1;
		} while (ui_EOC != 1);
      /************************************************/
		/*Read the digital value of the calibration Gain */
      /************************************************/
		/* data[0] = inl (devpriv->iobase+i_Offset + 28); */
		data[0] =
			inl(devpriv->iobase +
			s_BoardInfos[dev->minor].i_Offset + 28);
	}			/* if (i_InterruptFlag == ADDIDATA_DISABLE) */
	return 0;
}