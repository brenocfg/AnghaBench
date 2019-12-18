#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ irq; scalar_t__ iobase; } ;
struct comedi_cmd {int flags; int stop_arg; int chanlist_len; scalar_t__ convert_src; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {scalar_t__ dma_chan; scalar_t__ timer_mode; int adc_byte_count; size_t current_buffer; int timer_running; int control_state; TYPE_3__ timer; int /*<<< orphan*/  dma_transfer_size; int /*<<< orphan*/ * dma_buffer_addr; } ;
struct TYPE_4__ {int size; size_t ai_pg; } ;

/* Variables and functions */
 unsigned int BURST_LEN_BITS (int) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS1600_BURST ; 
 int DAS1600_BURST_VAL ; 
 scalar_t__ DAS1600_CONV ; 
 int DAS1600_CONV_DISABLE ; 
 scalar_t__ DAS16_CONTROL ; 
 scalar_t__ DAS16_GAIN ; 
 int DAS16_INTE ; 
 scalar_t__ DAS16_MUX ; 
 scalar_t__ DAS16_PACER ; 
 scalar_t__ DAS16_STATUS ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,int /*<<< orphan*/ ) ; 
 int DMA_ENABLE ; 
 int EXT_PACER ; 
 int INT_PACER ; 
 int PACING_MASK ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 int TRIG_RT ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (scalar_t__) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int** das16_gainlists ; 
 size_t das16_pg_none ; 
 int /*<<< orphan*/  das16_set_pacer (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  das16_suggest_transfer_size (struct comedi_device*,struct comedi_cmd) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  enable_dma (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* thisboard ; 
 scalar_t__ timer_period () ; 

__attribute__((used)) static int das16_cmd_exec(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int byte;
	unsigned long flags;
	int range;

	if (devpriv->dma_chan == 0 || (dev->irq == 0
				       && devpriv->timer_mode == 0)) {
		comedi_error(dev,
			     "irq (or use of 'timer mode') dma required to execute comedi_cmd");
		return -1;
	}
	if (cmd->flags & TRIG_RT) {
		comedi_error(dev,
			     "isa dma transfers cannot be performed with TRIG_RT, aborting");
		return -1;
	}

	devpriv->adc_byte_count =
	    cmd->stop_arg * cmd->chanlist_len * sizeof(uint16_t);

	/*  disable conversions for das1600 mode */
	if (thisboard->size > 0x400) {
		outb(DAS1600_CONV_DISABLE, dev->iobase + DAS1600_CONV);
	}
	/*  set scan limits */
	byte = CR_CHAN(cmd->chanlist[0]);
	byte |= CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]) << 4;
	outb(byte, dev->iobase + DAS16_MUX);

	/* set gain (this is also burst rate register but according to
	 * computer boards manual, burst rate does nothing, even on keithley cards) */
	if (thisboard->ai_pg != das16_pg_none) {
		range = CR_RANGE(cmd->chanlist[0]);
		outb((das16_gainlists[thisboard->ai_pg])[range],
		     dev->iobase + DAS16_GAIN);
	}

	/* set counter mode and counts */
	cmd->convert_arg =
	    das16_set_pacer(dev, cmd->convert_arg,
			    cmd->flags & TRIG_ROUND_MASK);
	DEBUG_PRINT("pacer period: %d ns\n", cmd->convert_arg);

	/* enable counters */
	byte = 0;
	/* Enable burst mode if appropriate. */
	if (thisboard->size > 0x400) {
		if (cmd->convert_src == TRIG_NOW) {
			outb(DAS1600_BURST_VAL, dev->iobase + DAS1600_BURST);
			/*  set burst length */
			byte |= BURST_LEN_BITS(cmd->chanlist_len - 1);
		} else {
			outb(0, dev->iobase + DAS1600_BURST);
		}
	}
	outb(byte, dev->iobase + DAS16_PACER);

	/*  set up dma transfer */
	flags = claim_dma_lock();
	disable_dma(devpriv->dma_chan);
	/* clear flip-flop to make sure 2-byte registers for
	 * count and address get set correctly */
	clear_dma_ff(devpriv->dma_chan);
	devpriv->current_buffer = 0;
	set_dma_addr(devpriv->dma_chan,
		     devpriv->dma_buffer_addr[devpriv->current_buffer]);
	/*  set appropriate size of transfer */
	devpriv->dma_transfer_size = das16_suggest_transfer_size(dev, *cmd);
	set_dma_count(devpriv->dma_chan, devpriv->dma_transfer_size);
	enable_dma(devpriv->dma_chan);
	release_dma_lock(flags);

	/*  set up interrupt */
	if (devpriv->timer_mode) {
		devpriv->timer_running = 1;
		devpriv->timer.expires = jiffies + timer_period();
		add_timer(&devpriv->timer);
		devpriv->control_state &= ~DAS16_INTE;
	} else {
		/* clear interrupt bit */
		outb(0x00, dev->iobase + DAS16_STATUS);
		/* enable interrupts */
		devpriv->control_state |= DAS16_INTE;
	}
	devpriv->control_state |= DMA_ENABLE;
	devpriv->control_state &= ~PACING_MASK;
	if (cmd->convert_src == TRIG_EXT)
		devpriv->control_state |= EXT_PACER;
	else
		devpriv->control_state |= INT_PACER;
	outb(devpriv->control_state, dev->iobase + DAS16_CONTROL);

	/* Enable conversions if using das1600 mode */
	if (thisboard->size > 0x400) {
		outb(0, dev->iobase + DAS1600_CONV);
	}

	return 0;
}