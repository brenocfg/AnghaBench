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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ b_Timer2Mode; int b_DigitalOutputRegister; scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned short APCI3120_FC_TIMER ; 
 scalar_t__ APCI3120_RD_STATUS ; 
 int APCI3120_SELECT_TIMER_2_HIGH_WORD ; 
 int APCI3120_SELECT_TIMER_2_LOW_WORD ; 
 scalar_t__ APCI3120_TIMER ; 
 scalar_t__ APCI3120_TIMER_CRT0 ; 
 scalar_t__ APCI3120_TIMER_STATUS_REGISTER ; 
 scalar_t__ APCI3120_TIMER_VALUE ; 
 scalar_t__ APCI3120_WATCHDOG ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

int i_APCI3120_InsnReadTimer(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned char b_Tmp;
	unsigned short us_TmpValue, us_TmpValue_2, us_StatusValue;

	if ((devpriv->b_Timer2Mode != APCI3120_WATCHDOG)
		&& (devpriv->b_Timer2Mode != APCI3120_TIMER)) {
		comedi_error(dev, "\nread:timer2  not configured ");
	}

	/* this_board->i_hwdrv_InsnReadTimer(dev,data); */
	if (devpriv->b_Timer2Mode == APCI3120_TIMER) {

		/* Read the LOW unsigned short of Timer 2 register */
		b_Tmp = ((devpriv->
				b_DigitalOutputRegister) & 0xF0) |
			APCI3120_SELECT_TIMER_2_LOW_WORD;
		outb(b_Tmp, devpriv->iobase + APCI3120_TIMER_CRT0);

		us_TmpValue = inw(devpriv->iobase + APCI3120_TIMER_VALUE);

		/* Read the HIGH unsigned short of Timer 2 register */
		b_Tmp = ((devpriv->
				b_DigitalOutputRegister) & 0xF0) |
			APCI3120_SELECT_TIMER_2_HIGH_WORD;
		outb(b_Tmp, devpriv->iobase + APCI3120_TIMER_CRT0);

		us_TmpValue_2 = inw(devpriv->iobase + APCI3120_TIMER_VALUE);

		/*  combining both words */
		data[0] = (unsigned int) ((us_TmpValue) | ((us_TmpValue_2) << 16));

	} else			/*  Read watch dog status */
	{

		us_StatusValue = inw(devpriv->iobase + APCI3120_RD_STATUS);
		us_StatusValue =
			((us_StatusValue & APCI3120_FC_TIMER) >> 12) & 1;
		if (us_StatusValue == 1) {
			/*  RESET FC_TIMER BIT */
			inb(devpriv->iobase + APCI3120_TIMER_STATUS_REGISTER);
		}
		data[0] = us_StatusValue;	/*  when data[0] = 1 then the watch dog has rundown */
	}
	return insn->n;
}