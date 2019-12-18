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
struct TYPE_2__ {unsigned int b_TimerSelectMode; scalar_t__ iobase; int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
 unsigned int ADDIDATA_TIMER ; 
 unsigned int ADDIDATA_WATCHDOG ; 
 scalar_t__ APCI3501_TCW_PROG ; 
 scalar_t__ APCI3501_TCW_RELOAD_VALUE ; 
 scalar_t__ APCI3501_TCW_TIMEBASE ; 
 scalar_t__ APCI3501_WATCHDOG ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI3501_ConfigTimerCounterWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ul_Command1 = 0;
	devpriv->tsk_Current = current;
	if (data[0] == ADDIDATA_WATCHDOG) {

		devpriv->b_TimerSelectMode = ADDIDATA_WATCHDOG;
		/* Disable the watchdog */
		outl(0x0, devpriv->iobase + APCI3501_WATCHDOG + APCI3501_TCW_PROG);	/* disable Wa */

		if (data[1] == 1) {
			/* Enable TIMER int & DISABLE ALL THE OTHER int SOURCES */
			outl(0x02,
				devpriv->iobase + APCI3501_WATCHDOG +
				APCI3501_TCW_PROG);
		} else {
			outl(0x0, devpriv->iobase + APCI3501_WATCHDOG + APCI3501_TCW_PROG);	/* disable Timer interrupt */
		}

		/* Loading the Timebase value */
		outl(data[2],
			devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_TIMEBASE);

		/* Loading the Reload value */
		outl(data[3],
			devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_RELOAD_VALUE);
		/* Set the mode */
		ul_Command1 = inl(devpriv->iobase + APCI3501_WATCHDOG + APCI3501_TCW_PROG) | 0xFFF819E0UL;	/* e2->e0 */
		outl(ul_Command1,
			devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_PROG);
	}			/* end if(data[0]==ADDIDATA_WATCHDOG) */

	else if (data[0] == ADDIDATA_TIMER) {
		/* First Stop The Timer */
		ul_Command1 =
			inl(devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_PROG);
		ul_Command1 = ul_Command1 & 0xFFFFF9FEUL;
		outl(ul_Command1, devpriv->iobase + APCI3501_WATCHDOG + APCI3501_TCW_PROG);	/* Stop The Timer */
		devpriv->b_TimerSelectMode = ADDIDATA_TIMER;
		if (data[1] == 1) {
			/* Enable TIMER int & DISABLE ALL THE OTHER int SOURCES */
			outl(0x02,
				devpriv->iobase + APCI3501_WATCHDOG +
				APCI3501_TCW_PROG);
		} else {
			outl(0x0, devpriv->iobase + APCI3501_WATCHDOG + APCI3501_TCW_PROG);	/* disable Timer interrupt */
		}

		/*  Loading Timebase */
		outl(data[2],
			devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_TIMEBASE);

		/* Loading the Reload value */
		outl(data[3],
			devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_RELOAD_VALUE);

		/*  printk ("\nTimer Address :: %x\n", (devpriv->iobase+APCI3501_WATCHDOG)); */
		ul_Command1 =
			inl(devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_PROG);
		ul_Command1 =
			(ul_Command1 & 0xFFF719E2UL) | 2UL << 13UL | 0x10UL;
		outl(ul_Command1, devpriv->iobase + APCI3501_WATCHDOG + APCI3501_TCW_PROG);	/* mode 2 */

	}			/* end if(data[0]==ADDIDATA_TIMER) */

	return insn->n;
}