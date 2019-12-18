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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned short us_OutputRegister; scalar_t__ b_ModeSelectRegister; scalar_t__ b_ExttrigEnable; scalar_t__ b_Timer2Interrupt; scalar_t__ b_Timer2Mode; scalar_t__ b_OutputMemoryStatus; scalar_t__ ui_EocEosConversionTime; int /*<<< orphan*/  b_InterruptMode; void* b_EocEosInterrupt; void* b_AiCyclicAcquisition; } ;

/* Variables and functions */
 int APCI3120_ANALOG_OP_CHANNEL_1 ; 
 int APCI3120_ANALOG_OP_CHANNEL_2 ; 
 int APCI3120_ANALOG_OP_CHANNEL_3 ; 
 int APCI3120_ANALOG_OP_CHANNEL_4 ; 
 int APCI3120_ANALOG_OP_CHANNEL_5 ; 
 int APCI3120_ANALOG_OP_CHANNEL_6 ; 
 int APCI3120_ANALOG_OP_CHANNEL_7 ; 
 int APCI3120_ANALOG_OP_CHANNEL_8 ; 
 scalar_t__ APCI3120_ANALOG_OUTPUT_1 ; 
 scalar_t__ APCI3120_ANALOG_OUTPUT_2 ; 
 void* APCI3120_DISABLE ; 
 int /*<<< orphan*/  APCI3120_EOC_MODE ; 
 scalar_t__ APCI3120_RD_STATUS ; 
 scalar_t__ APCI3120_RESET_FIFO ; 
 scalar_t__ APCI3120_SEQ_RAM_ADDRESS ; 
 scalar_t__ APCI3120_WRITE_MODE_SELECT ; 
 scalar_t__ APCI3120_WR_ADDRESS ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

int i_APCI3120_Reset(struct comedi_device *dev)
{
	unsigned int i;
	unsigned short us_TmpValue;

	devpriv->b_AiCyclicAcquisition = APCI3120_DISABLE;
	devpriv->b_EocEosInterrupt = APCI3120_DISABLE;
	devpriv->b_InterruptMode = APCI3120_EOC_MODE;
	devpriv->ui_EocEosConversionTime = 0;	/*  set eoc eos conv time to 0 */
	devpriv->b_OutputMemoryStatus = 0;

	/*  variables used in timer subdevice */
	devpriv->b_Timer2Mode = 0;
	devpriv->b_Timer2Interrupt = 0;
	devpriv->b_ExttrigEnable = 0;	/*  Disable ext trigger */

	/* Disable all interrupts, watchdog for the anolog output */
	devpriv->b_ModeSelectRegister = 0;
	outb(devpriv->b_ModeSelectRegister,
		dev->iobase + APCI3120_WRITE_MODE_SELECT);

	/*  Disables all counters, ext trigger and clears PA, PR */
	devpriv->us_OutputRegister = 0;
	outw(devpriv->us_OutputRegister, dev->iobase + APCI3120_WR_ADDRESS);

/*
 * Code to set the all anolog o/p channel to 0v 8191 is decimal
 * value for zero(0 v)volt in bipolar mode(default)
 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_1, dev->iobase + APCI3120_ANALOG_OUTPUT_1);	/* channel 1 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_2, dev->iobase + APCI3120_ANALOG_OUTPUT_1);	/* channel 2 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_3, dev->iobase + APCI3120_ANALOG_OUTPUT_1);	/* channel 3 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_4, dev->iobase + APCI3120_ANALOG_OUTPUT_1);	/* channel 4 */

	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_5, dev->iobase + APCI3120_ANALOG_OUTPUT_2);	/* channel 5 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_6, dev->iobase + APCI3120_ANALOG_OUTPUT_2);	/* channel 6 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_7, dev->iobase + APCI3120_ANALOG_OUTPUT_2);	/* channel 7 */
	outw(8191 | APCI3120_ANALOG_OP_CHANNEL_8, dev->iobase + APCI3120_ANALOG_OUTPUT_2);	/* channel 8 */

	/*   Reset digital output to L0W */

/* ES05  outb(0x0,dev->iobase+APCI3120_DIGITAL_OUTPUT); */
	udelay(10);

	inw(dev->iobase + 0);	/* make a dummy read */
	inb(dev->iobase + APCI3120_RESET_FIFO);	/*  flush FIFO */
	inw(dev->iobase + APCI3120_RD_STATUS);	/*  flush A/D status register */

	/* code to reset the RAM sequence */
	for (i = 0; i < 16; i++) {
		us_TmpValue = i << 8;	/* select the location */
		outw(us_TmpValue, dev->iobase + APCI3120_SEQ_RAM_ADDRESS);
	}
	return 0;
}