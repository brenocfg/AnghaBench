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
struct comedi_subdevice {int n_chan; TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned char chanlist_len; scalar_t__ stop_src; int stop_arg; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_4__ {int ai_scans_left; } ;
struct TYPE_3__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int DMM32AT_ADINT ; 
 int /*<<< orphan*/  DMM32AT_AICONF ; 
 int /*<<< orphan*/  DMM32AT_AIHIGH ; 
 int /*<<< orphan*/  DMM32AT_AILOW ; 
 int /*<<< orphan*/  DMM32AT_AIRBACK ; 
 int /*<<< orphan*/  DMM32AT_CNTRL ; 
 int /*<<< orphan*/  DMM32AT_CONV ; 
 int /*<<< orphan*/  DMM32AT_FIFOCNTRL ; 
 int DMM32AT_FIFORESET ; 
 int /*<<< orphan*/  DMM32AT_INTCLOCK ; 
 int DMM32AT_INTRESET ; 
 int DMM32AT_SCANENABLE ; 
 unsigned char DMM32AT_STATUS ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ TRIG_COUNT ; 
 TYPE_2__* devpriv ; 
 int* dmm32at_rangebits ; 
 int /*<<< orphan*/  dmm32at_setaitimer (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned char dmm_inb (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmm_outb (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int dmm32at_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	int i, range;
	unsigned char chanlo, chanhi, status;

	if (!cmd->chanlist)
		return -EINVAL;

	/* get the channel list and range */
	chanlo = CR_CHAN(cmd->chanlist[0]) & (s->n_chan - 1);
	chanhi = chanlo + cmd->chanlist_len - 1;
	if (chanhi >= s->n_chan)
		return -EINVAL;
	range = CR_RANGE(cmd->chanlist[0]);

	/* reset fifo */
	dmm_outb(dev, DMM32AT_FIFOCNTRL, DMM32AT_FIFORESET);

	/* set scan enable */
	dmm_outb(dev, DMM32AT_FIFOCNTRL, DMM32AT_SCANENABLE);

	/* write the ai channel range regs */
	dmm_outb(dev, DMM32AT_AILOW, chanlo);
	dmm_outb(dev, DMM32AT_AIHIGH, chanhi);

	/* set the range bits */
	dmm_outb(dev, DMM32AT_AICONF, dmm32at_rangebits[range]);

	/* reset the interrupt just in case */
	dmm_outb(dev, DMM32AT_CNTRL, DMM32AT_INTRESET);

	if (cmd->stop_src == TRIG_COUNT)
		devpriv->ai_scans_left = cmd->stop_arg;
	else {			/* TRIG_NONE */
		devpriv->ai_scans_left = 0xffffffff;	/* indicates TRIG_NONE to isr */
	}

	/* wait for circuit to settle */
	for (i = 0; i < 40000; i++) {
		status = dmm_inb(dev, DMM32AT_AIRBACK);
		if ((status & DMM32AT_STATUS) == 0)
			break;
	}
	if (i == 40000) {
		printk("timeout\n");
		return -ETIMEDOUT;
	}

	if (devpriv->ai_scans_left > 1) {
		/* start the clock and enable the interrupts */
		dmm32at_setaitimer(dev, cmd->scan_begin_arg);
	} else {
		/* start the interrups and initiate a single scan */
		dmm_outb(dev, DMM32AT_INTCLOCK, DMM32AT_ADINT);
		dmm_outb(dev, DMM32AT_CONV, 0xff);
	}

/* 	printk("dmmat32 in command\n"); */

/* 	for(i=0;i<cmd->chanlist_len;i++) */
/* 		comedi_buf_put(s->async,i*100); */

/* 	s->async->events |= COMEDI_CB_EOA; */
/* 	comedi_event(dev, s); */

	return 0;

}