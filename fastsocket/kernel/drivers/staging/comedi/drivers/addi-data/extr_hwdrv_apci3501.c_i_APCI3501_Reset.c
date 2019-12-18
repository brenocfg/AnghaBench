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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3501_ANALOG_OUTPUT ; 
 scalar_t__ APCI3501_AO_PROG ; 
 scalar_t__ APCI3501_AO_VOLT_MODE ; 
 scalar_t__ APCI3501_DIGITAL_OP ; 
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI3501_Reset(struct comedi_device *dev)
{
	int i_Count = 0, i_temp = 0;
	unsigned int ul_Command1 = 0, ul_Polarity, ul_DAC_Ready = 0;
	outl(0x0, devpriv->iobase + APCI3501_DIGITAL_OP);
	outl(1, devpriv->iobase + APCI3501_ANALOG_OUTPUT +
		APCI3501_AO_VOLT_MODE);

	ul_Polarity = 0x80000000;

	for (i_Count = 0; i_Count <= 7; i_Count++) {
		ul_DAC_Ready = inl(devpriv->iobase + APCI3501_ANALOG_OUTPUT);

		while (ul_DAC_Ready == 0) {
			ul_DAC_Ready =
				inl(devpriv->iobase + APCI3501_ANALOG_OUTPUT);
			ul_DAC_Ready = (ul_DAC_Ready >> 8) & 1;
		}

		if (ul_DAC_Ready) {
			/*  Output the Value on the output channels. */
			ul_Command1 =
				(unsigned int) ((unsigned int) (i_Count & 0xFF) |
				(unsigned int) ((i_temp << 0x8) & 0x7FFFFF00L) |
				(unsigned int) (ul_Polarity));
			outl(ul_Command1,
				devpriv->iobase + APCI3501_ANALOG_OUTPUT +
				APCI3501_AO_PROG);
		}
	}

	return 0;
}