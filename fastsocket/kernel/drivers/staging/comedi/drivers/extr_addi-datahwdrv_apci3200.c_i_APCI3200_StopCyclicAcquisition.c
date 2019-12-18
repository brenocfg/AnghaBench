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
struct comedi_device {size_t minor; } ;
struct TYPE_4__ {scalar_t__ iobase; } ;
struct TYPE_3__ {scalar_t__ i_Offset; scalar_t__ i_Sum; scalar_t__ i_Count; scalar_t__ i_Initialised; scalar_t__ i_InterruptFlag; } ;

/* Variables and functions */
 TYPE_2__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 TYPE_1__* s_BoardInfos ; 

int i_APCI3200_StopCyclicAcquisition(struct comedi_device *dev, struct comedi_subdevice *s)
{
	unsigned int ui_Configuration = 0;
	/* i_InterruptFlag=0; */
	/* i_Initialised=0; */
	/* i_Count=0; */
	/* i_Sum=0; */
	s_BoardInfos[dev->minor].i_InterruptFlag = 0;
	s_BoardInfos[dev->minor].i_Initialised = 0;
	s_BoardInfos[dev->minor].i_Count = 0;
	s_BoardInfos[dev->minor].i_Sum = 0;

  /*******************/
	/*Read the register */
  /*******************/
	/* ui_Configuration = inl(devpriv->iobase+i_Offset + 8); */
	ui_Configuration =
		inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 8);
  /*****************************/
	/*Reset the START and IRQ bit */
  /*****************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl((ui_Configuration & 0xFFE7FFFF),devpriv->iobase+i_Offset + 8); */
	outl((ui_Configuration & 0xFFE7FFFF),
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 8);
	return 0;
}