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
 unsigned int ADDIDATA_ENABLE ; 
 unsigned int ADDIDATA_TIMER ; 
 unsigned int ADDIDATA_WATCHDOG ; 
 int EINVAL ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 scalar_t__ i_Temp ; 
 int i_WatchdogNbr ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI035_ConfigTimerWatchdog(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_Status = 0;
	unsigned int ui_Command = 0;
	unsigned int ui_Mode = 0;
	i_Temp = 0;
	devpriv->tsk_Current = current;
	devpriv->b_TimerSelectMode = data[0];
	i_WatchdogNbr = data[1];
	if (data[0] == 0) {
		ui_Mode = 2;
	} else {
		ui_Mode = 0;
	}
/* ui_Command = inl(devpriv->iobase+((i_WatchdogNbr-1)*32)+12); */
	ui_Command = 0;
/* ui_Command = ui_Command & 0xFFFFF9FEUL; */
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
	ui_Command = 0;
	ui_Command = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
/************************/
/* Set the reload value */
/************************/
	outl(data[3], devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 4);
/*********************/
/* Set the time unit */
/*********************/
	outl(data[2], devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 8);
	if (data[0] == ADDIDATA_TIMER) {

		 /******************************/
		/* Set the mode :             */
		/* - Disable the hardware     */
		/* - Disable the counter mode */
		/* - Disable the warning      */
		/* - Disable the reset        */
		/* - Enable the timer mode    */
		/* - Set the timer mode       */
		 /******************************/

		ui_Command =
			(ui_Command & 0xFFF719E2UL) | ui_Mode << 13UL | 0x10UL;

	}			/* if (data[0] == ADDIDATA_TIMER) */
	else {
		if (data[0] == ADDIDATA_WATCHDOG) {

		 /******************************/
			/* Set the mode :             */
			/* - Disable the hardware     */
			/* - Disable the counter mode */
			/* - Disable the warning      */
			/* - Disable the reset        */
			/* - Disable the timer mode   */
		 /******************************/

			ui_Command = ui_Command & 0xFFF819E2UL;

		} else {
			printk("\n The parameter for Timer/watchdog selection is in error\n");
			return -EINVAL;
		}
	}
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
	ui_Command = 0;
	ui_Command = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
/********************************/
/* Disable the hardware trigger */
/********************************/
	ui_Command = ui_Command & 0xFFFFF89FUL;
	if (data[4] == ADDIDATA_ENABLE) {
    /**********************************/
		/* Set the hardware trigger level */
    /**********************************/
		ui_Command = ui_Command | (data[5] << 5);
	}
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
	ui_Command = 0;
	ui_Command = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
/*****************************/
/* Disable the hardware gate */
/*****************************/
	ui_Command = ui_Command & 0xFFFFF87FUL;
	if (data[6] == ADDIDATA_ENABLE) {
/*******************************/
/* Set the hardware gate level */
/*******************************/
		ui_Command = ui_Command | (data[7] << 7);
	}
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
	ui_Command = 0;
	ui_Command = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
/*******************************/
/* Disable the hardware output */
/*******************************/
	ui_Command = ui_Command & 0xFFFFF9FBUL;
/*********************************/
/* Set the hardware output level */
/*********************************/
	ui_Command = ui_Command | (data[8] << 2);
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
	if (data[9] == ADDIDATA_ENABLE) {
   /************************/
		/* Set the reload value */
   /************************/
		outl(data[11],
			devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 24);
   /**********************/
		/* Set the time unite */
   /**********************/
		outl(data[10],
			devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 28);
	}

	ui_Command = 0;
	ui_Command = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
 /*******************************/
	/* Disable the hardware output */
 /*******************************/
	ui_Command = ui_Command & 0xFFFFF9F7UL;
   /*********************************/
	/* Set the hardware output level */
   /*********************************/
	ui_Command = ui_Command | (data[12] << 3);
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
 /*************************************/
 /**  Enable the watchdog interrupt  **/
 /*************************************/
	ui_Command = 0;
	ui_Command = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);
/*******************************/
/* Set the interrupt selection */
/*******************************/
	ui_Status = inl(devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 16);

	ui_Command = (ui_Command & 0xFFFFF9FDUL) | (data[13] << 1);
	outl(ui_Command, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 12);

	return insn->n;
}