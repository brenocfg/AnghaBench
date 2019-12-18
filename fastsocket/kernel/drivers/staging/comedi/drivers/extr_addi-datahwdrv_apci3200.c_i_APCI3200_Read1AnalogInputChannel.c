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
struct comedi_insn {int dummy; } ;
struct comedi_device {size_t minor; } ;
struct TYPE_4__ {scalar_t__ iobase; } ;
struct TYPE_3__ {unsigned int i_ChannelNo; unsigned int i_ADDIDATAConversionTimeUnit; unsigned int i_ADDIDATAConversionTime; scalar_t__ i_InterruptFlag; scalar_t__ i_Offset; } ;

/* Variables and functions */
 scalar_t__ ADDIDATA_DISABLE ; 
 scalar_t__ ADDIDATA_ENABLE ; 
 TYPE_2__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 TYPE_1__* s_BoardInfos ; 

int i_APCI3200_Read1AnalogInputChannel(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_EOC = 0;
	unsigned int ui_ChannelNo = 0;
	unsigned int ui_CommandRegister = 0;

	/* BEGIN JK 06.07.04: Management of sevrals boards */
	/* ui_ChannelNo=i_ChannelNo; */
	ui_ChannelNo = s_BoardInfos[dev->minor].i_ChannelNo;

	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
  /*********************************/
	/* Write the channel to configure */
  /*********************************/
	/* Begin JK 20.10.2004: Bad channel value is used when using differential mode */
	/* outl(0 | ui_Channel_num , devpriv->iobase+i_Offset + 0x4); */
	/* outl(0 | s_BoardInfos [dev->minor].ui_Channel_num , devpriv->iobase+s_BoardInfos [dev->minor].i_Offset + 0x4); */
	outl(0 | s_BoardInfos[dev->minor].i_ChannelNo,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 0x4);
	/* End JK 20.10.2004: Bad channel value is used when using differential mode */

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

  /**************************************************************************/
	/* Set the start end stop index to the selected channel and set the start */
  /**************************************************************************/

	ui_CommandRegister = ui_ChannelNo | (ui_ChannelNo << 8) | 0x80000;

  /*********************************/
	/*Test if the interrupt is enable */
  /*********************************/

	/* if (i_InterruptFlag == ADDIDATA_ENABLE) */
	if (s_BoardInfos[dev->minor].i_InterruptFlag == ADDIDATA_ENABLE) {
      /************************/
		/* Enable the interrupt */
      /************************/
		ui_CommandRegister = ui_CommandRegister | 0x00100000;
	}			/* if (i_InterruptFlag == ADDIDATA_ENABLE) */

  /******************************/
	/* Write the command register */
  /******************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;

	/* outl(ui_CommandRegister, devpriv->iobase+i_Offset + 8); */
	outl(ui_CommandRegister,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 8);

  /*****************************/
	/*Test if interrupt is enable */
  /*****************************/
	/* if (i_InterruptFlag == ADDIDATA_DISABLE) */
	if (s_BoardInfos[dev->minor].i_InterruptFlag == ADDIDATA_DISABLE) {
		do {
	  /*************************/
			/*Read the EOC Status bit */
	  /*************************/

			/* ui_EOC = inl(devpriv->iobase+i_Offset + 20) & 1; */
			ui_EOC = inl(devpriv->iobase +
				s_BoardInfos[dev->minor].i_Offset + 20) & 1;

		} while (ui_EOC != 1);

      /***************************************/
		/* Read the digital value of the input */
      /***************************************/

		/* data[0] = inl (devpriv->iobase+i_Offset + 28); */
		data[0] =
			inl(devpriv->iobase +
			s_BoardInfos[dev->minor].i_Offset + 28);
		/* END JK 06.07.04: Management of sevrals boards */

	}			/*  if (i_InterruptFlag == ADDIDATA_DISABLE) */
	return 0;
}