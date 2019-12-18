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
struct comedi_cmd {unsigned int chanlist_len; int scan_begin_src; scalar_t__ stop_src; int stop_arg; int /*<<< orphan*/  flags; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;
struct TYPE_2__ {int ao_count; int /*<<< orphan*/  ao_control_bits; int /*<<< orphan*/  ao_divisor2; scalar_t__ pacer_counter_dio; int /*<<< orphan*/  ao_divisor1; scalar_t__ ao_registers; scalar_t__ control_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC8254 ; 
 scalar_t__ DACFIFOCLR ; 
 int /*<<< orphan*/  DAC_CHAN_EN (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC_CSR ; 
 int /*<<< orphan*/  DAC_PACER_EXT_RISE ; 
 int /*<<< orphan*/  DAC_PACER_INT ; 
 int /*<<< orphan*/  DAC_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_BASE ; 
 scalar_t__ TRIG_COUNT ; 
#define  TRIG_EXT 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  cb_pcidas_ao_inttrig ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8254_load (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ao_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int i;
	unsigned long flags;

	/*  set channel limits, gain */
	spin_lock_irqsave(&dev->spinlock, flags);
	for (i = 0; i < cmd->chanlist_len; i++) {
		/*  enable channel */
		devpriv->ao_control_bits |=
		    DAC_CHAN_EN(CR_CHAN(cmd->chanlist[i]));
		/*  set range */
		devpriv->ao_control_bits |= DAC_RANGE(CR_CHAN(cmd->chanlist[i]),
						      CR_RANGE(cmd->
							       chanlist[i]));
	}

	/*  disable analog out before settings pacer source and count values */
	outw(devpriv->ao_control_bits, devpriv->control_status + DAC_CSR);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  clear fifo */
	outw(0, devpriv->ao_registers + DACFIFOCLR);

	/*  load counters */
	if (cmd->scan_begin_src == TRIG_TIMER) {
		i8253_cascade_ns_to_timer_2div(TIMER_BASE,
					       &(devpriv->ao_divisor1),
					       &(devpriv->ao_divisor2),
					       &(cmd->scan_begin_arg),
					       cmd->flags);

		/* Write the values of ctr1 and ctr2 into counters 1 and 2 */
		i8254_load(devpriv->pacer_counter_dio + DAC8254, 0, 1,
			   devpriv->ao_divisor1, 2);
		i8254_load(devpriv->pacer_counter_dio + DAC8254, 0, 2,
			   devpriv->ao_divisor2, 2);
	}
	/*  set number of conversions */
	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->ao_count = cmd->chanlist_len * cmd->stop_arg;
	}
	/*  set pacer source */
	spin_lock_irqsave(&dev->spinlock, flags);
	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		devpriv->ao_control_bits |= DAC_PACER_INT;
		break;
	case TRIG_EXT:
		devpriv->ao_control_bits |= DAC_PACER_EXT_RISE;
		break;
	default:
		spin_unlock_irqrestore(&dev->spinlock, flags);
		comedi_error(dev, "error setting dac pacer source");
		return -1;
		break;
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	async->inttrig = cb_pcidas_ao_inttrig;

	return 0;
}