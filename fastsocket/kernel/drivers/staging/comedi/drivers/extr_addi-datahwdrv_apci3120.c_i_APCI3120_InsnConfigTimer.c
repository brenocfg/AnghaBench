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
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned char b_Timer2Interrupt; int us_OutputRegister; int b_ModeSelectRegister; int b_TimerSelectMode; int b_DigitalOutputRegister; unsigned int b_Timer2Mode; scalar_t__ iobase; } ;
struct TYPE_3__ {int /*<<< orphan*/  pc_DriverName; } ;

/* Variables and functions */
 int APCI3120_DISABLE_EOC_INT ; 
 int APCI3120_DISABLE_EOS_INT ; 
 int APCI3120_DISABLE_TIMER2 ; 
 int APCI3120_DISABLE_TIMER_INT ; 
 scalar_t__ APCI3120_RD_STATUS ; 
 int APCI3120_SELECT_TIMER_2_HIGH_WORD ; 
 int APCI3120_SELECT_TIMER_2_LOW_WORD ; 
 unsigned int APCI3120_TIMER ; 
 int APCI3120_TIMER_2_MODE_2 ; 
 int APCI3120_TIMER_2_MODE_5 ; 
 scalar_t__ APCI3120_TIMER_CRT0 ; 
 scalar_t__ APCI3120_TIMER_CRT1 ; 
 scalar_t__ APCI3120_TIMER_VALUE ; 
 unsigned int APCI3120_WATCHDOG ; 
 scalar_t__ APCI3120_WRITE_MODE_SELECT ; 
 scalar_t__ APCI3120_WR_ADDRESS ; 
 int HIWORD (unsigned int) ; 
 int LOWORD (unsigned int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* this_board ; 

int i_APCI3120_InsnConfigTimer(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{

	unsigned int ui_Timervalue2;
	unsigned short us_TmpValue;
	unsigned char b_Tmp;

	if (!data[1])
		comedi_error(dev, "config:No timer constant !");

	devpriv->b_Timer2Interrupt = (unsigned char) data[2];	/*  save info whether to enable or disable interrupt */

	ui_Timervalue2 = data[1] / 1000;	/*  convert nano seconds  to u seconds */

	/* this_board->i_hwdrv_InsnConfigTimer(dev, ui_Timervalue2,(unsigned char)data[0]); */
	us_TmpValue = (unsigned short) inw(devpriv->iobase + APCI3120_RD_STATUS);

/*
 * EL250804: Testing if board APCI3120 have the new Quartz or if it
 * is an APCI3001 and calculate the time value to set in the timer
 */
	if ((us_TmpValue & 0x00B0) == 0x00B0
		|| !strcmp(this_board->pc_DriverName, "apci3001")) {
		/* Calculate the time value to set in the timer */
		ui_Timervalue2 = ui_Timervalue2 / 50;
	} else {
		/* Calculate the time value to set in the timer */
		ui_Timervalue2 = ui_Timervalue2 / 70;
	}

	/* Reset gate 2 of Timer 2 to disable it (Set Bit D14 to 0) */
	devpriv->us_OutputRegister =
		devpriv->us_OutputRegister & APCI3120_DISABLE_TIMER2;
	outw(devpriv->us_OutputRegister, devpriv->iobase + APCI3120_WR_ADDRESS);

	/*  Disable TIMER Interrupt */
	devpriv->b_ModeSelectRegister =
		devpriv->
		b_ModeSelectRegister & APCI3120_DISABLE_TIMER_INT & 0xEF;

	/*  Disable Eoc and Eos Interrupts */
	devpriv->b_ModeSelectRegister =
		devpriv->
		b_ModeSelectRegister & APCI3120_DISABLE_EOC_INT &
		APCI3120_DISABLE_EOS_INT;
	outb(devpriv->b_ModeSelectRegister,
		devpriv->iobase + APCI3120_WRITE_MODE_SELECT);
	if (data[0] == APCI3120_TIMER)	/* initialize timer */
	{
		/* devpriv->b_ModeSelectRegister=devpriv->b_ModeSelectRegister |
		 * APCI3120_ENABLE_TIMER_INT; */

		/* outb(devpriv->b_ModeSelectRegister,devpriv->iobase+APCI3120_WRITE_MODE_SELECT); */

		/* Set the Timer 2 in mode 2(Timer) */
		devpriv->b_TimerSelectMode =
			(devpriv->
			b_TimerSelectMode & 0x0F) | APCI3120_TIMER_2_MODE_2;
		outb(devpriv->b_TimerSelectMode,
			devpriv->iobase + APCI3120_TIMER_CRT1);

/*
 * Configure the timer 2 for writing the LOW unsigned short of timer
 * is Delay value You must make a b_tmp variable with
 * DigitalOutPutRegister because at Address_1+APCI3120_TIMER_CRT0
 * you can set the digital output and configure the timer 2,and if
 * you don't make this, digital output are erase (Set to 0)
 */

		/* Writing LOW unsigned short */
		b_Tmp = ((devpriv->
				b_DigitalOutputRegister) & 0xF0) |
			APCI3120_SELECT_TIMER_2_LOW_WORD;
		outb(b_Tmp, devpriv->iobase + APCI3120_TIMER_CRT0);
		outw(LOWORD(ui_Timervalue2),
			devpriv->iobase + APCI3120_TIMER_VALUE);

		/* Writing HIGH unsigned short */
		b_Tmp = ((devpriv->
				b_DigitalOutputRegister) & 0xF0) |
			APCI3120_SELECT_TIMER_2_HIGH_WORD;
		outb(b_Tmp, devpriv->iobase + APCI3120_TIMER_CRT0);
		outw(HIWORD(ui_Timervalue2),
			devpriv->iobase + APCI3120_TIMER_VALUE);
		/*  timer2 in Timer mode enabled */
		devpriv->b_Timer2Mode = APCI3120_TIMER;

	} else			/*  Initialize Watch dog */
	{

		/* Set the Timer 2 in mode 5(Watchdog) */

		devpriv->b_TimerSelectMode =
			(devpriv->
			b_TimerSelectMode & 0x0F) | APCI3120_TIMER_2_MODE_5;
		outb(devpriv->b_TimerSelectMode,
			devpriv->iobase + APCI3120_TIMER_CRT1);

/*
 * Configure the timer 2 for writing the LOW unsigned short of timer
 * is Delay value You must make a b_tmp variable with
 * DigitalOutPutRegister because at Address_1+APCI3120_TIMER_CRT0
 * you can set the digital output and configure the timer 2,and if
 * you don't make this, digital output are erase (Set to 0)
 */

		/* Writing LOW unsigned short */
		b_Tmp = ((devpriv->
				b_DigitalOutputRegister) & 0xF0) |
			APCI3120_SELECT_TIMER_2_LOW_WORD;
		outb(b_Tmp, devpriv->iobase + APCI3120_TIMER_CRT0);
		outw(LOWORD(ui_Timervalue2),
			devpriv->iobase + APCI3120_TIMER_VALUE);

		/* Writing HIGH unsigned short */
		b_Tmp = ((devpriv->
				b_DigitalOutputRegister) & 0xF0) |
			APCI3120_SELECT_TIMER_2_HIGH_WORD;
		outb(b_Tmp, devpriv->iobase + APCI3120_TIMER_CRT0);

		outw(HIWORD(ui_Timervalue2),
			devpriv->iobase + APCI3120_TIMER_VALUE);
		/* watchdog enabled */
		devpriv->b_Timer2Mode = APCI3120_WATCHDOG;

	}

	return insn->n;

}