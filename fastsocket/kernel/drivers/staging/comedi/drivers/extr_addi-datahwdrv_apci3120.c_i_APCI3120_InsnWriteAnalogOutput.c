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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3120_ANALOG_OUTPUT_1 ; 
 scalar_t__ APCI3120_ANALOG_OUTPUT_2 ; 
 scalar_t__ APCI3120_RD_STATUS ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

int i_APCI3120_InsnWriteAnalogOutput(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	unsigned int ui_Range, ui_Channel;
	unsigned short us_TmpValue;

	ui_Range = CR_RANGE(insn->chanspec);
	ui_Channel = CR_CHAN(insn->chanspec);

	/* this_board->i_hwdrv_InsnWriteAnalogOutput(dev, ui_Range, ui_Channel,data[0]); */
	if (ui_Range)		/*  if 1 then unipolar */
	{

		if (data[0] != 0)
			data[0] =
				((((ui_Channel & 0x03) << 14) & 0xC000) | (1 <<
					13) | (data[0] + 8191));
		else
			data[0] =
				((((ui_Channel & 0x03) << 14) & 0xC000) | (1 <<
					13) | 8192);

	} else			/*  if 0 then   bipolar */
	{
		data[0] =
			((((ui_Channel & 0x03) << 14) & 0xC000) | (0 << 13) |
			data[0]);

	}

/*
 * out put n values at the given channel. printk("\nwaiting for
 * DA_READY BIT");
 */
	do			/* Waiting of DA_READY BIT */
	{
		us_TmpValue =
			((unsigned short) inw(devpriv->iobase +
				APCI3120_RD_STATUS)) & 0x0001;
	} while (us_TmpValue != 0x0001);

	if (ui_Channel <= 3)
/*
 * for channel 0-3 out at the register 1 (wrDac1-8) data[i]
 * typecasted to ushort since word write is to be done
 */
		outw((unsigned short) data[0],
			devpriv->iobase + APCI3120_ANALOG_OUTPUT_1);
	else
/*
 * for channel 4-7 out at the register 2 (wrDac5-8) data[i]
 * typecasted to ushort since word write is to be done
 */
		outw((unsigned short) data[0],
			devpriv->iobase + APCI3120_ANALOG_OUTPUT_2);

	return insn->n;
}