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
typedef  int /*<<< orphan*/  uint8_t ;
struct enc_private {int /*<<< orphan*/  (* SetEnable ) (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ;} ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ irq; int /*<<< orphan*/  minor; } ;
struct comedi_cmd {int scan_begin_src; int flags; int const start_src; int convert_src; int stop_src; int /*<<< orphan*/  start_arg; int /*<<< orphan*/  stop_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/  scan_begin_arg; } ;
struct TYPE_4__ {int ai_cmd_running; int ai_continous; scalar_t__ base_addr; int /*<<< orphan*/  ai_sample_count; scalar_t__ ai_convert_count; } ;
struct TYPE_3__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKENAB_ALWAYS ; 
 int /*<<< orphan*/  CLKENAB_INDEX ; 
 int /*<<< orphan*/  DEBUG (char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int IRQ_GPIO3 ; 
 int IRQ_RPS1 ; 
 int /*<<< orphan*/  MC1_ERPS1 ; 
 int /*<<< orphan*/  MC_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_IER ; 
 scalar_t__ P_ISR ; 
 int /*<<< orphan*/  P_MC1 ; 
 int /*<<< orphan*/  ResetADC (struct comedi_device*,int /*<<< orphan*/ *) ; 
#define  TRIG_COUNT 134 
#define  TRIG_EXT 133 
#define  TRIG_FOLLOW 132 
#define  TRIG_INT 131 
#define  TRIG_NONE 130 
#define  TRIG_NOW 129 
 int TRIG_ROUND_MASK ; 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 struct enc_private* encpriv ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s626_ai_inttrig ; 
 int /*<<< orphan*/  s626_ai_load_polllist (int /*<<< orphan*/ *,struct comedi_cmd*) ; 
 int /*<<< orphan*/  s626_dio_clear_irq (struct comedi_device*) ; 
 int /*<<< orphan*/  s626_dio_set_irq (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int s626_ns_to_timer (int*,int) ; 
 int /*<<< orphan*/  s626_timer_load (struct comedi_device*,struct enc_private*,int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s626_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{

	uint8_t ppl[16];
	struct comedi_cmd *cmd = &s->async->cmd;
	struct enc_private *k;
	int tick;

	DEBUG("s626_ai_cmd: entering command function\n");

	if (devpriv->ai_cmd_running) {
		printk("s626_ai_cmd: Another ai_cmd is running %d\n",
		       dev->minor);
		return -EBUSY;
	}
	/* disable interrupt */
	writel(0, devpriv->base_addr + P_IER);

	/* clear interrupt request */
	writel(IRQ_RPS1 | IRQ_GPIO3, devpriv->base_addr + P_ISR);

	/* clear any pending interrupt */
	s626_dio_clear_irq(dev);
	/*   s626_enc_clear_irq(dev); */

	/* reset ai_cmd_running flag */
	devpriv->ai_cmd_running = 0;

	/*  test if cmd is valid */
	if (cmd == NULL) {
		DEBUG("s626_ai_cmd: NULL command\n");
		return -EINVAL;
	} else {
		DEBUG("s626_ai_cmd: command recieved!!!\n");
	}

	if (dev->irq == 0) {
		comedi_error(dev,
			     "s626_ai_cmd: cannot run command without an irq");
		return -EIO;
	}

	s626_ai_load_polllist(ppl, cmd);
	devpriv->ai_cmd_running = 1;
	devpriv->ai_convert_count = 0;

	switch (cmd->scan_begin_src) {
	case TRIG_FOLLOW:
		break;
	case TRIG_TIMER:
		/*  set a conter to generate adc trigger at scan_begin_arg interval */
		k = &encpriv[5];
		tick = s626_ns_to_timer((int *)&cmd->scan_begin_arg,
					cmd->flags & TRIG_ROUND_MASK);

		/* load timer value and enable interrupt */
		s626_timer_load(dev, k, tick);
		k->SetEnable(dev, k, CLKENAB_ALWAYS);

		DEBUG("s626_ai_cmd: scan trigger timer is set with value %d\n",
		      tick);

		break;
	case TRIG_EXT:
		/*  set the digital line and interrupt for scan trigger */
		if (cmd->start_src != TRIG_EXT)
			s626_dio_set_irq(dev, cmd->scan_begin_arg);

		DEBUG("s626_ai_cmd: External scan trigger is set!!!\n");

		break;
	}

	switch (cmd->convert_src) {
	case TRIG_NOW:
		break;
	case TRIG_TIMER:
		/*  set a conter to generate adc trigger at convert_arg interval */
		k = &encpriv[4];
		tick = s626_ns_to_timer((int *)&cmd->convert_arg,
					cmd->flags & TRIG_ROUND_MASK);

		/* load timer value and enable interrupt */
		s626_timer_load(dev, k, tick);
		k->SetEnable(dev, k, CLKENAB_INDEX);

		DEBUG
		    ("s626_ai_cmd: convert trigger timer is set with value %d\n",
		     tick);
		break;
	case TRIG_EXT:
		/*  set the digital line and interrupt for convert trigger */
		if (cmd->scan_begin_src != TRIG_EXT
		    && cmd->start_src == TRIG_EXT)
			s626_dio_set_irq(dev, cmd->convert_arg);

		DEBUG("s626_ai_cmd: External convert trigger is set!!!\n");

		break;
	}

	switch (cmd->stop_src) {
	case TRIG_COUNT:
		/*  data arrives as one packet */
		devpriv->ai_sample_count = cmd->stop_arg;
		devpriv->ai_continous = 0;
		break;
	case TRIG_NONE:
		/*  continous aquisition */
		devpriv->ai_continous = 1;
		devpriv->ai_sample_count = 0;
		break;
	}

	ResetADC(dev, ppl);

	switch (cmd->start_src) {
	case TRIG_NOW:
		/*  Trigger ADC scan loop start by setting RPS Signal 0. */
		/*  MC_ENABLE( P_MC2, MC2_ADC_RPS ); */

		/*  Start executing the RPS program. */
		MC_ENABLE(P_MC1, MC1_ERPS1);

		DEBUG("s626_ai_cmd: ADC triggered\n");
		s->async->inttrig = NULL;
		break;
	case TRIG_EXT:
		/* configure DIO channel for acquisition trigger */
		s626_dio_set_irq(dev, cmd->start_arg);

		DEBUG("s626_ai_cmd: External start trigger is set!!!\n");

		s->async->inttrig = NULL;
		break;
	case TRIG_INT:
		s->async->inttrig = s626_ai_inttrig;
		break;
	}

	/* enable interrupt */
	writel(IRQ_GPIO3 | IRQ_RPS1, devpriv->base_addr + P_IER);

	DEBUG("s626_ai_cmd: command function terminated\n");

	return 0;
}