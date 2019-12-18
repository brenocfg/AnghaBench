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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct comedi_cmd {int chanlist_len; scalar_t__ convert_src; scalar_t__ scan_begin_src; int flags; scalar_t__ stop_src; int stop_arg; scalar_t__ start_src; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_2__ {int count; unsigned int adc_fifo_bits; scalar_t__ control_status; scalar_t__ adc_fifo; } ;

/* Variables and functions */
 scalar_t__ ADCFIFOCLR ; 
 scalar_t__ ADCMUX_CONT ; 
 scalar_t__ AREF_DIFF ; 
 unsigned int BEGIN_SCAN (int /*<<< orphan*/ ) ; 
 unsigned int BURSTE ; 
 scalar_t__ CALIBRATION_REG ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 unsigned int END_SCAN (int /*<<< orphan*/ ) ; 
 unsigned int EOAI ; 
 unsigned int EXT_TRIGGER ; 
 unsigned int GAIN_BITS (int) ; 
 unsigned int INT ; 
 unsigned int INTE ; 
 scalar_t__ INT_ADCFIFO ; 
 unsigned int INT_EOS ; 
 unsigned int INT_FHF ; 
 unsigned int INT_FNE ; 
 unsigned int INT_MASK ; 
 int IS_UNIPOLAR ; 
 unsigned int LADFUL ; 
 unsigned int PACER_EXT_RISE ; 
 unsigned int PACER_INT ; 
 unsigned int SE ; 
 unsigned int SW_TRIGGER ; 
 unsigned int TGEN ; 
 scalar_t__ TRIG_CONTSTAT ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 scalar_t__ TRIG_TIMER ; 
 int TRIG_WAKE_EOS ; 
 unsigned int UNIP ; 
 unsigned int XTRCL ; 
 int /*<<< orphan*/  cb_pcidas_load_counters (struct comedi_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ai_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int bits;
	unsigned long flags;

	/*  make sure CAL_EN_BIT is disabled */
	outw(0, devpriv->control_status + CALIBRATION_REG);
	/*  initialize before settings pacer source and count values */
	outw(0, devpriv->control_status + TRIG_CONTSTAT);
	/*  clear fifo */
	outw(0, devpriv->adc_fifo + ADCFIFOCLR);

	/*  set mux limits, gain and pacer source */
	bits = BEGIN_SCAN(CR_CHAN(cmd->chanlist[0])) |
	    END_SCAN(CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1])) |
	    GAIN_BITS(CR_RANGE(cmd->chanlist[0]));
	/*  set unipolar/bipolar */
	if (CR_RANGE(cmd->chanlist[0]) & IS_UNIPOLAR)
		bits |= UNIP;
	/*  set singleended/differential */
	if (CR_AREF(cmd->chanlist[0]) != AREF_DIFF)
		bits |= SE;
	/*  set pacer source */
	if (cmd->convert_src == TRIG_EXT || cmd->scan_begin_src == TRIG_EXT)
		bits |= PACER_EXT_RISE;
	else
		bits |= PACER_INT;
	outw(bits, devpriv->control_status + ADCMUX_CONT);

#ifdef CB_PCIDAS_DEBUG
	printk("comedi: sent 0x%x to adcmux control\n", bits);
#endif

	/*  load counters */
	if (cmd->convert_src == TRIG_TIMER)
		cb_pcidas_load_counters(dev, &cmd->convert_arg,
					cmd->flags & TRIG_ROUND_MASK);
	else if (cmd->scan_begin_src == TRIG_TIMER)
		cb_pcidas_load_counters(dev, &cmd->scan_begin_arg,
					cmd->flags & TRIG_ROUND_MASK);

	/*  set number of conversions */
	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->count = cmd->chanlist_len * cmd->stop_arg;
	}
	/*  enable interrupts */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->adc_fifo_bits |= INTE;
	devpriv->adc_fifo_bits &= ~INT_MASK;
	if (cmd->flags & TRIG_WAKE_EOS) {
		if (cmd->convert_src == TRIG_NOW && cmd->chanlist_len > 1)
			devpriv->adc_fifo_bits |= INT_EOS;	/*  interrupt end of burst */
		else
			devpriv->adc_fifo_bits |= INT_FNE;	/*  interrupt fifo not empty */
	} else {
		devpriv->adc_fifo_bits |= INT_FHF;	/* interrupt fifo half full */
	}
#ifdef CB_PCIDAS_DEBUG
	printk("comedi: adc_fifo_bits are 0x%x\n", devpriv->adc_fifo_bits);
#endif
	/*  enable (and clear) interrupts */
	outw(devpriv->adc_fifo_bits | EOAI | INT | LADFUL,
	     devpriv->control_status + INT_ADCFIFO);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  set start trigger and burst mode */
	bits = 0;
	if (cmd->start_src == TRIG_NOW)
		bits |= SW_TRIGGER;
	else if (cmd->start_src == TRIG_EXT)
		bits |= EXT_TRIGGER | TGEN | XTRCL;
	else {
		comedi_error(dev, "bug!");
		return -1;
	}
	if (cmd->convert_src == TRIG_NOW && cmd->chanlist_len > 1)
		bits |= BURSTE;
	outw(bits, devpriv->control_status + TRIG_CONTSTAT);
#ifdef CB_PCIDAS_DEBUG
	printk("comedi: sent 0x%x to trig control\n", bits);
#endif

	return 0;
}