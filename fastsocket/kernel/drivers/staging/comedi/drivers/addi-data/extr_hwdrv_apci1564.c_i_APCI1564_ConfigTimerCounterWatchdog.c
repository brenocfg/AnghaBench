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
struct TYPE_2__ {unsigned int b_TimerSelectMode; unsigned int b_ModeSelectRegister; scalar_t__ iobase; scalar_t__ i_IobaseAmcc; int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
 unsigned int ADDIDATA_COUNTER ; 
 unsigned int ADDIDATA_TIMER ; 
 unsigned int ADDIDATA_WATCHDOG ; 
 scalar_t__ APCI1564_COUNTER1 ; 
 scalar_t__ APCI1564_COUNTER2 ; 
 scalar_t__ APCI1564_COUNTER3 ; 
 scalar_t__ APCI1564_COUNTER4 ; 
 scalar_t__ APCI1564_DIGITAL_IP ; 
 scalar_t__ APCI1564_DIGITAL_IP_IRQ ; 
 scalar_t__ APCI1564_DIGITAL_OP ; 
 scalar_t__ APCI1564_DIGITAL_OP_IRQ ; 
 scalar_t__ APCI1564_DIGITAL_OP_WATCHDOG ; 
 scalar_t__ APCI1564_TCW_IRQ ; 
 scalar_t__ APCI1564_TCW_PROG ; 
 scalar_t__ APCI1564_TCW_RELOAD_VALUE ; 
 scalar_t__ APCI1564_TCW_TIMEBASE ; 
 scalar_t__ APCI1564_TIMER ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1564_ConfigTimerCounterWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ul_Command1 = 0;
	devpriv->tsk_Current = current;
	if (data[0] == ADDIDATA_WATCHDOG) {
		devpriv->b_TimerSelectMode = ADDIDATA_WATCHDOG;

		/* Disable the watchdog */
		outl(0x0,
			devpriv->i_IobaseAmcc + APCI1564_DIGITAL_OP_WATCHDOG +
			APCI1564_TCW_PROG);
		/* Loading the Reload value */
		outl(data[3],
			devpriv->i_IobaseAmcc + APCI1564_DIGITAL_OP_WATCHDOG +
			APCI1564_TCW_RELOAD_VALUE);
	}			/*  if  (data[0]==ADDIDATA_WATCHDOG) */
	else if (data[0] == ADDIDATA_TIMER) {
		/* First Stop The Timer */
		ul_Command1 =
			inl(devpriv->i_IobaseAmcc + APCI1564_TIMER +
			APCI1564_TCW_PROG);
		ul_Command1 = ul_Command1 & 0xFFFFF9FEUL;
		outl(ul_Command1, devpriv->i_IobaseAmcc + APCI1564_TIMER + APCI1564_TCW_PROG);	/* Stop The Timer */

		devpriv->b_TimerSelectMode = ADDIDATA_TIMER;
		if (data[1] == 1) {
			outl(0x02, devpriv->i_IobaseAmcc + APCI1564_TIMER + APCI1564_TCW_PROG);	/* Enable TIMER int & DISABLE ALL THE OTHER int SOURCES */
			outl(0x0,
				devpriv->i_IobaseAmcc + APCI1564_DIGITAL_IP +
				APCI1564_DIGITAL_IP_IRQ);
			outl(0x0,
				devpriv->i_IobaseAmcc + APCI1564_DIGITAL_OP +
				APCI1564_DIGITAL_OP_IRQ);
			outl(0x0,
				devpriv->i_IobaseAmcc +
				APCI1564_DIGITAL_OP_WATCHDOG +
				APCI1564_TCW_IRQ);
			outl(0x0,
				devpriv->iobase + APCI1564_COUNTER1 +
				APCI1564_TCW_IRQ);
			outl(0x0,
				devpriv->iobase + APCI1564_COUNTER2 +
				APCI1564_TCW_IRQ);
			outl(0x0,
				devpriv->iobase + APCI1564_COUNTER3 +
				APCI1564_TCW_IRQ);
			outl(0x0,
				devpriv->iobase + APCI1564_COUNTER4 +
				APCI1564_TCW_IRQ);
		}		/*  if  (data[1]==1) */
		else {
			outl(0x0, devpriv->i_IobaseAmcc + APCI1564_TIMER + APCI1564_TCW_PROG);	/* disable Timer interrupt */
		}		/*  else if  (data[1]==1) */

		/*  Loading Timebase */

		outl(data[2],
			devpriv->i_IobaseAmcc + APCI1564_TIMER +
			APCI1564_TCW_TIMEBASE);

		/* Loading the Reload value */
		outl(data[3],
			devpriv->i_IobaseAmcc + APCI1564_TIMER +
			APCI1564_TCW_RELOAD_VALUE);

		ul_Command1 =
			inl(devpriv->i_IobaseAmcc + APCI1564_TIMER +
			APCI1564_TCW_PROG);
		ul_Command1 =
			(ul_Command1 & 0xFFF719E2UL) | 2UL << 13UL | 0x10UL;
		outl(ul_Command1, devpriv->i_IobaseAmcc + APCI1564_TIMER + APCI1564_TCW_PROG);	/* mode 2 */
	}			/*  else if  (data[0]==ADDIDATA_TIMER) */
	else if (data[0] == ADDIDATA_COUNTER) {
		devpriv->b_TimerSelectMode = ADDIDATA_COUNTER;
		devpriv->b_ModeSelectRegister = data[5];

		/* First Stop The Counter */
		ul_Command1 =
			inl(devpriv->iobase + ((data[5] - 1) * 0x20) +
			APCI1564_TCW_PROG);
		ul_Command1 = ul_Command1 & 0xFFFFF9FEUL;
		outl(ul_Command1, devpriv->iobase + ((data[5] - 1) * 0x20) + APCI1564_TCW_PROG);	/* Stop The Timer */

      /************************/
		/* Set the reload value */
      /************************/
		outl(data[3],
			devpriv->iobase + ((data[5] - 1) * 0x20) +
			APCI1564_TCW_RELOAD_VALUE);

      /******************************/
		/* Set the mode :             */
		/* - Disable the hardware     */
		/* - Disable the counter mode */
		/* - Disable the warning      */
		/* - Disable the reset        */
		/* - Disable the timer mode   */
		/* - Enable the counter mode  */
      /******************************/
		ul_Command1 =
			(ul_Command1 & 0xFFFC19E2UL) | 0x80000UL |
			(unsigned int) ((unsigned int) data[4] << 16UL);
		outl(ul_Command1,
			devpriv->iobase + ((data[5] - 1) * 0x20) +
			APCI1564_TCW_PROG);

		/*  Enable or Disable Interrupt */
		ul_Command1 = (ul_Command1 & 0xFFFFF9FD) | (data[1] << 1);
		outl(ul_Command1,
			devpriv->iobase + ((data[5] - 1) * 0x20) +
			APCI1564_TCW_PROG);

      /*****************************/
		/* Set the Up/Down selection */
      /*****************************/
		ul_Command1 = (ul_Command1 & 0xFFFBF9FFUL) | (data[6] << 18);
		outl(ul_Command1,
			devpriv->iobase + ((data[5] - 1) * 0x20) +
			APCI1564_TCW_PROG);
	}			/*  else if  (data[0]==ADDIDATA_COUNTER) */
	else {
		printk(" Invalid subdevice.");
	}			/*  else if  (data[0]==ADDIDATA_WATCHDOG) */

	return insn->n;
}