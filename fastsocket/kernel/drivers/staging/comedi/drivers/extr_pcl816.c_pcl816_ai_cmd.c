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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int irq; scalar_t__ iobase; } ;
struct comedi_cmd {scalar_t__ start_src; scalar_t__ scan_begin_src; scalar_t__ scan_end_src; scalar_t__ scan_end_arg; scalar_t__ chanlist_len; int convert_src; scalar_t__ convert_arg; int flags; scalar_t__ stop_src; scalar_t__ stop_arg; int /*<<< orphan*/  chanlist; } ;
struct TYPE_6__ {int irq_blocked; int ai_neverending; int dma; unsigned int* hwdmasize; unsigned int dma_runs_to_end; unsigned int last_dma_run; int /*<<< orphan*/  int816_mode; int /*<<< orphan*/ * hwdmaptr; scalar_t__ next_dma_buf; scalar_t__ ai_scans; scalar_t__ irq_was_now_closed; scalar_t__ ai_poll_ptr; scalar_t__ ai_act_scan; } ;
struct TYPE_5__ {scalar_t__ ai_ns_min; int /*<<< orphan*/  i8254_osc_base; } ;
struct TYPE_4__ {struct comedi_cmd cmd; scalar_t__ cur_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_TYPE_AI1_DMA ; 
 int /*<<< orphan*/  INT_TYPE_AI3_DMA ; 
 scalar_t__ PCL816_CONTROL ; 
 scalar_t__ PCL816_STATUS ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
#define  TRIG_TIMER 128 
 int TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  check_and_setup_channel_list (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,unsigned int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned int) ; 
 int /*<<< orphan*/  set_dma_addr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int,unsigned int) ; 
 int /*<<< orphan*/  set_dma_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,int,unsigned int,unsigned int) ; 
 TYPE_2__* this_board ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcl816_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	unsigned int divisor1 = 0, divisor2 = 0, dma_flags, bytes, dmairq;
	struct comedi_cmd *cmd = &s->async->cmd;

	if (cmd->start_src != TRIG_NOW)
		return -EINVAL;
	if (cmd->scan_begin_src != TRIG_FOLLOW)
		return -EINVAL;
	if (cmd->scan_end_src != TRIG_COUNT)
		return -EINVAL;
	if (cmd->scan_end_arg != cmd->chanlist_len)
		return -EINVAL;
/* if(cmd->chanlist_len>MAX_CHANLIST_LEN) return -EINVAL; */
	if (devpriv->irq_blocked)
		return -EBUSY;

	if (cmd->convert_src == TRIG_TIMER) {
		if (cmd->convert_arg < this_board->ai_ns_min)
			cmd->convert_arg = this_board->ai_ns_min;

		i8253_cascade_ns_to_timer(this_board->i8254_osc_base, &divisor1,
					  &divisor2, &cmd->convert_arg,
					  cmd->flags & TRIG_ROUND_MASK);
		if (divisor1 == 1) {	/*  PCL816 crash if any divisor is set to 1 */
			divisor1 = 2;
			divisor2 /= 2;
		}
		if (divisor2 == 1) {
			divisor2 = 2;
			divisor1 /= 2;
		}
	}

	start_pacer(dev, -1, 0, 0);	/*  stop pacer */

	if (!check_and_setup_channel_list(dev, s, cmd->chanlist,
					  cmd->chanlist_len))
		return -EINVAL;
	udelay(1);

	devpriv->ai_act_scan = 0;
	s->async->cur_chan = 0;
	devpriv->irq_blocked = 1;
	devpriv->ai_poll_ptr = 0;
	devpriv->irq_was_now_closed = 0;

	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->ai_scans = cmd->stop_arg;
		devpriv->ai_neverending = 0;
	} else {
		devpriv->ai_scans = 0;
		devpriv->ai_neverending = 1;
	}

	if ((cmd->flags & TRIG_WAKE_EOS)) {	/*  don't we want wake up every scan? */
		printk("pl816: You wankt WAKE_EOS but I dont want handle it");
		/*               devpriv->ai_eos=1; */
		/* if (devpriv->ai_n_chan==1) */
		/*       devpriv->dma=0; // DMA is useless for this situation */
	}

	if (devpriv->dma) {
		bytes = devpriv->hwdmasize[0];
		if (!devpriv->ai_neverending) {
			bytes = s->async->cmd.chanlist_len * s->async->cmd.chanlist_len * sizeof(short);	/*  how many */
			devpriv->dma_runs_to_end = bytes / devpriv->hwdmasize[0];	/*  how many DMA pages we must fill */
			devpriv->last_dma_run = bytes % devpriv->hwdmasize[0];	/* on last dma transfer must be moved */
			devpriv->dma_runs_to_end--;
			if (devpriv->dma_runs_to_end >= 0)
				bytes = devpriv->hwdmasize[0];
		} else
			devpriv->dma_runs_to_end = -1;

		devpriv->next_dma_buf = 0;
		set_dma_mode(devpriv->dma, DMA_MODE_READ);
		dma_flags = claim_dma_lock();
		clear_dma_ff(devpriv->dma);
		set_dma_addr(devpriv->dma, devpriv->hwdmaptr[0]);
		set_dma_count(devpriv->dma, bytes);
		release_dma_lock(dma_flags);
		enable_dma(devpriv->dma);
	}

	start_pacer(dev, 1, divisor1, divisor2);
	dmairq = ((devpriv->dma & 0x3) << 4) | (dev->irq & 0x7);

	switch (cmd->convert_src) {
	case TRIG_TIMER:
		devpriv->int816_mode = INT_TYPE_AI1_DMA;
		outb(0x32, dev->iobase + PCL816_CONTROL);	/*  Pacer+IRQ+DMA */
		outb(dmairq, dev->iobase + PCL816_STATUS);	/*  write irq and DMA to card */
		break;

	default:
		devpriv->int816_mode = INT_TYPE_AI3_DMA;
		outb(0x34, dev->iobase + PCL816_CONTROL);	/*  Ext trig+IRQ+DMA */
		outb(dmairq, dev->iobase + PCL816_STATUS);	/*  write irq to card */
		break;
	}

	DPRINTK("pcl816 END: pcl812_ai_cmd()\n");
	return 0;
}