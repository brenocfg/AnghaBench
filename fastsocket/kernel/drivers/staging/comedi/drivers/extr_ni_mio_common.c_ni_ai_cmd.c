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
struct comedi_device {scalar_t__ irq; } ;
struct comedi_cmd {int chanlist_len; int start_src; int start_arg; int stop_src; int scan_begin_src; int scan_begin_arg; int convert_src; int convert_arg; int flags; int /*<<< orphan*/  stop_arg; int /*<<< orphan*/  chanlist; } ;
struct TYPE_6__ {scalar_t__ reg_type; } ;
struct TYPE_5__ {unsigned int an_trig_etc_reg; int ai_cmd2; int ai_continuous; int aimode; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  int_a_enable_reg; int /*<<< orphan*/  (* stc_writel ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
#define  AIMODE_HALF_FULL 136 
#define  AIMODE_SAMPLE 135 
#define  AIMODE_SCAN 134 
 int AI_CONVERT_Source_Polarity ; 
 int AI_CONVERT_Source_Select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AI_Command_1_Register ; 
 int /*<<< orphan*/  AI_Command_2_Register ; 
 int AI_Configuration_End ; 
 unsigned int AI_Configuration_Start ; 
 int AI_Continuous ; 
 int AI_DIV_Arm ; 
 int AI_End_On_End_Of_Scan ; 
 int AI_Error_Interrupt_Ack ; 
 int AI_Error_Interrupt_Enable ; 
 int AI_FIFO_Interrupt_Enable ; 
 int AI_FIFO_Mode_HF ; 
 int AI_FIFO_Mode_HF_to_E ; 
 int AI_FIFO_Mode_NE ; 
 int /*<<< orphan*/  AI_Mode_1_Register ; 
 int AI_Mode_1_Reserved ; 
 int /*<<< orphan*/  AI_Mode_2_Register ; 
 int /*<<< orphan*/  AI_Mode_3_Register ; 
 int AI_Pre_Trigger ; 
 int AI_SC_Arm ; 
 int AI_SC_Gate_Enable ; 
 int AI_SC_Initial_Load_Source ; 
 int AI_SC_Load ; 
 int /*<<< orphan*/  AI_SC_Load_A_Registers ; 
 int AI_SC_Reload_Mode ; 
 int AI_SC_TC_Error_Confirm ; 
 int AI_SC_TC_Interrupt_Ack ; 
 int AI_SC_TC_Interrupt_Enable ; 
 int AI_SI2_Arm ; 
 int AI_SI2_Initial_Load_Source ; 
 int AI_SI2_Load ; 
 int /*<<< orphan*/  AI_SI2_Load_A_Register ; 
 int /*<<< orphan*/  AI_SI2_Load_B_Register ; 
 int AI_SI2_Reload_Mode ; 
 int AI_SI_Arm ; 
 int AI_SI_Initial_Load_Source ; 
 int AI_SI_Load ; 
 int /*<<< orphan*/  AI_SI_Load_A_Registers ; 
 int AI_SI_Reload_Mode (int /*<<< orphan*/ ) ; 
 unsigned int AI_START1_Edge ; 
 int AI_START1_Interrupt_Ack ; 
 unsigned int AI_START1_Polarity ; 
 int AI_START1_Pulse ; 
 unsigned int AI_START1_Select (int) ; 
 unsigned int AI_START1_Sync ; 
 int AI_START2_Interrupt_Ack ; 
 unsigned int AI_START2_Select (int /*<<< orphan*/ ) ; 
 int AI_START_Edge ; 
 int AI_START_Interrupt_Ack ; 
 int AI_START_Polarity ; 
 int /*<<< orphan*/  AI_START_STOP_Select_Register ; 
 int AI_START_Select (int /*<<< orphan*/ ) ; 
 int AI_START_Sync ; 
 int AI_STOP_Edge ; 
 int AI_STOP_Interrupt_Ack ; 
 int AI_STOP_Interrupt_Enable ; 
 int AI_STOP_Polarity ; 
 int AI_STOP_Select (int) ; 
 int AI_STOP_Sync ; 
 int AI_Start_Stop ; 
 int AI_Start_Stop_Gate_Enable ; 
 int AI_Trigger_Once ; 
 int /*<<< orphan*/  AI_Trigger_Select_Register ; 
 unsigned int Analog_Trigger_Enable ; 
 int /*<<< orphan*/  Analog_Trigger_Etc_Register ; 
 int CR_CHAN (int) ; 
 int CR_EDGE ; 
 int CR_INVERT ; 
 int EIO ; 
 int /*<<< orphan*/  Interrupt_A_Ack_Register ; 
 int /*<<< orphan*/  Interrupt_A_Enable_Register ; 
 int /*<<< orphan*/  Joint_Reset_Register ; 
 int /*<<< orphan*/  MDPRINTK (char*,...) ; 
#define  TRIG_COUNT 133 
#define  TRIG_EXT 132 
#define  TRIG_INT 131 
#define  TRIG_NONE 130 
#define  TRIG_NOW 129 
 int /*<<< orphan*/  TRIG_ROUND_NEAREST ; 
#define  TRIG_TIMER 128 
 int TRIG_WAKE_EOS ; 
 TYPE_3__ boardtype ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  ni_ai_inttrig ; 
 int ni_ai_setup_MITE_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_clear_ai_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_load_channelgain_list (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int ni_ns_to_timer (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ni_reg_611x ; 
 scalar_t__ ni_reg_6143 ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int,int) ; 
 unsigned int num_adc_stages_611x ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub24 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub27 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub28 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub29 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub30 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub31 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub32 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub33 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub34 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	const struct comedi_cmd *cmd = &s->async->cmd;
	int timer;
	int mode1 = 0;		/* mode1 is needed for both stop and convert */
	int mode2 = 0;
	int start_stop_select = 0;
	unsigned int stop_count;
	int interrupt_a_enable = 0;

	MDPRINTK("ni_ai_cmd\n");
	if (dev->irq == 0) {
		comedi_error(dev, "cannot run command without an irq");
		return -EIO;
	}
	ni_clear_ai_fifo(dev);

	ni_load_channelgain_list(dev, cmd->chanlist_len, cmd->chanlist);

	/* start configuration */
	devpriv->stc_writew(dev, AI_Configuration_Start, Joint_Reset_Register);

	/* disable analog triggering for now, since it
	 * interferes with the use of pfi0 */
	devpriv->an_trig_etc_reg &= ~Analog_Trigger_Enable;
	devpriv->stc_writew(dev, devpriv->an_trig_etc_reg,
			    Analog_Trigger_Etc_Register);

	switch (cmd->start_src) {
	case TRIG_INT:
	case TRIG_NOW:
		devpriv->stc_writew(dev, AI_START2_Select(0) |
				    AI_START1_Sync | AI_START1_Edge |
				    AI_START1_Select(0),
				    AI_Trigger_Select_Register);
		break;
	case TRIG_EXT:
		{
			int chan = CR_CHAN(cmd->start_arg);
			unsigned int bits = AI_START2_Select(0) |
			    AI_START1_Sync | AI_START1_Select(chan + 1);

			if (cmd->start_arg & CR_INVERT)
				bits |= AI_START1_Polarity;
			if (cmd->start_arg & CR_EDGE)
				bits |= AI_START1_Edge;
			devpriv->stc_writew(dev, bits,
					    AI_Trigger_Select_Register);
			break;
		}
	}

	mode2 &= ~AI_Pre_Trigger;
	mode2 &= ~AI_SC_Initial_Load_Source;
	mode2 &= ~AI_SC_Reload_Mode;
	devpriv->stc_writew(dev, mode2, AI_Mode_2_Register);

	if (cmd->chanlist_len == 1 || (boardtype.reg_type == ni_reg_611x)
	    || (boardtype.reg_type == ni_reg_6143)) {
		start_stop_select |= AI_STOP_Polarity;
		start_stop_select |= AI_STOP_Select(31);	/*  logic low */
		start_stop_select |= AI_STOP_Sync;
	} else {
		start_stop_select |= AI_STOP_Select(19);	/*  ai configuration memory */
	}
	devpriv->stc_writew(dev, start_stop_select,
			    AI_START_STOP_Select_Register);

	devpriv->ai_cmd2 = 0;
	switch (cmd->stop_src) {
	case TRIG_COUNT:
		stop_count = cmd->stop_arg - 1;

		if (boardtype.reg_type == ni_reg_611x) {
			/*  have to take 3 stage adc pipeline into account */
			stop_count += num_adc_stages_611x;
		}
		/* stage number of scans */
		devpriv->stc_writel(dev, stop_count, AI_SC_Load_A_Registers);

		mode1 |= AI_Start_Stop | AI_Mode_1_Reserved | AI_Trigger_Once;
		devpriv->stc_writew(dev, mode1, AI_Mode_1_Register);
		/* load SC (Scan Count) */
		devpriv->stc_writew(dev, AI_SC_Load, AI_Command_1_Register);

		devpriv->ai_continuous = 0;
		if (stop_count == 0) {
			devpriv->ai_cmd2 |= AI_End_On_End_Of_Scan;
			interrupt_a_enable |= AI_STOP_Interrupt_Enable;
			/*  this is required to get the last sample for chanlist_len > 1, not sure why */
			if (cmd->chanlist_len > 1)
				start_stop_select |=
				    AI_STOP_Polarity | AI_STOP_Edge;
		}
		break;
	case TRIG_NONE:
		/* stage number of scans */
		devpriv->stc_writel(dev, 0, AI_SC_Load_A_Registers);

		mode1 |= AI_Start_Stop | AI_Mode_1_Reserved | AI_Continuous;
		devpriv->stc_writew(dev, mode1, AI_Mode_1_Register);

		/* load SC (Scan Count) */
		devpriv->stc_writew(dev, AI_SC_Load, AI_Command_1_Register);

		devpriv->ai_continuous = 1;

		break;
	}

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		/*
		   stop bits for non 611x boards
		   AI_SI_Special_Trigger_Delay=0
		   AI_Pre_Trigger=0
		   AI_START_STOP_Select_Register:
		   AI_START_Polarity=0 (?)      rising edge
		   AI_START_Edge=1              edge triggered
		   AI_START_Sync=1 (?)
		   AI_START_Select=0            SI_TC
		   AI_STOP_Polarity=0           rising edge
		   AI_STOP_Edge=0               level
		   AI_STOP_Sync=1
		   AI_STOP_Select=19            external pin (configuration mem)
		 */
		start_stop_select |= AI_START_Edge | AI_START_Sync;
		devpriv->stc_writew(dev, start_stop_select,
				    AI_START_STOP_Select_Register);

		mode2 |= AI_SI_Reload_Mode(0);
		/* AI_SI_Initial_Load_Source=A */
		mode2 &= ~AI_SI_Initial_Load_Source;
		/* mode2 |= AI_SC_Reload_Mode; */
		devpriv->stc_writew(dev, mode2, AI_Mode_2_Register);

		/* load SI */
		timer = ni_ns_to_timer(dev, cmd->scan_begin_arg,
				       TRIG_ROUND_NEAREST);
		devpriv->stc_writel(dev, timer, AI_SI_Load_A_Registers);
		devpriv->stc_writew(dev, AI_SI_Load, AI_Command_1_Register);
		break;
	case TRIG_EXT:
		if (cmd->scan_begin_arg & CR_EDGE)
			start_stop_select |= AI_START_Edge;
		/* AI_START_Polarity==1 is falling edge */
		if (cmd->scan_begin_arg & CR_INVERT)
			start_stop_select |= AI_START_Polarity;
		if (cmd->scan_begin_src != cmd->convert_src ||
		    (cmd->scan_begin_arg & ~CR_EDGE) !=
		    (cmd->convert_arg & ~CR_EDGE))
			start_stop_select |= AI_START_Sync;
		start_stop_select |=
		    AI_START_Select(1 + CR_CHAN(cmd->scan_begin_arg));
		devpriv->stc_writew(dev, start_stop_select,
				    AI_START_STOP_Select_Register);
		break;
	}

	switch (cmd->convert_src) {
	case TRIG_TIMER:
	case TRIG_NOW:
		if (cmd->convert_arg == 0 || cmd->convert_src == TRIG_NOW)
			timer = 1;
		else
			timer = ni_ns_to_timer(dev, cmd->convert_arg,
					       TRIG_ROUND_NEAREST);
		devpriv->stc_writew(dev, 1, AI_SI2_Load_A_Register);	/* 0,0 does not work. */
		devpriv->stc_writew(dev, timer, AI_SI2_Load_B_Register);

		/* AI_SI2_Reload_Mode = alternate */
		/* AI_SI2_Initial_Load_Source = A */
		mode2 &= ~AI_SI2_Initial_Load_Source;
		mode2 |= AI_SI2_Reload_Mode;
		devpriv->stc_writew(dev, mode2, AI_Mode_2_Register);

		/* AI_SI2_Load */
		devpriv->stc_writew(dev, AI_SI2_Load, AI_Command_1_Register);

		mode2 |= AI_SI2_Reload_Mode;	/*  alternate */
		mode2 |= AI_SI2_Initial_Load_Source;	/*  B */

		devpriv->stc_writew(dev, mode2, AI_Mode_2_Register);
		break;
	case TRIG_EXT:
		mode1 |= AI_CONVERT_Source_Select(1 + cmd->convert_arg);
		if ((cmd->convert_arg & CR_INVERT) == 0)
			mode1 |= AI_CONVERT_Source_Polarity;
		devpriv->stc_writew(dev, mode1, AI_Mode_1_Register);

		mode2 |= AI_Start_Stop_Gate_Enable | AI_SC_Gate_Enable;
		devpriv->stc_writew(dev, mode2, AI_Mode_2_Register);

		break;
	}

	if (dev->irq) {

		/* interrupt on FIFO, errors, SC_TC */
		interrupt_a_enable |= AI_Error_Interrupt_Enable |
		    AI_SC_TC_Interrupt_Enable;

#ifndef PCIDMA
		interrupt_a_enable |= AI_FIFO_Interrupt_Enable;
#endif

		if (cmd->flags & TRIG_WAKE_EOS
		    || (devpriv->ai_cmd2 & AI_End_On_End_Of_Scan)) {
			/* wake on end-of-scan */
			devpriv->aimode = AIMODE_SCAN;
		} else {
			devpriv->aimode = AIMODE_HALF_FULL;
		}

		switch (devpriv->aimode) {
		case AIMODE_HALF_FULL:
			/*generate FIFO interrupts and DMA requests on half-full */
#ifdef PCIDMA
			devpriv->stc_writew(dev, AI_FIFO_Mode_HF_to_E,
					    AI_Mode_3_Register);
#else
			devpriv->stc_writew(dev, AI_FIFO_Mode_HF,
					    AI_Mode_3_Register);
#endif
			break;
		case AIMODE_SAMPLE:
			/*generate FIFO interrupts on non-empty */
			devpriv->stc_writew(dev, AI_FIFO_Mode_NE,
					    AI_Mode_3_Register);
			break;
		case AIMODE_SCAN:
#ifdef PCIDMA
			devpriv->stc_writew(dev, AI_FIFO_Mode_NE,
					    AI_Mode_3_Register);
#else
			devpriv->stc_writew(dev, AI_FIFO_Mode_HF,
					    AI_Mode_3_Register);
#endif
			interrupt_a_enable |= AI_STOP_Interrupt_Enable;
			break;
		default:
			break;
		}

		devpriv->stc_writew(dev, AI_Error_Interrupt_Ack | AI_STOP_Interrupt_Ack | AI_START_Interrupt_Ack | AI_START2_Interrupt_Ack | AI_START1_Interrupt_Ack | AI_SC_TC_Interrupt_Ack | AI_SC_TC_Error_Confirm, Interrupt_A_Ack_Register);	/* clear interrupts */

		ni_set_bits(dev, Interrupt_A_Enable_Register,
			    interrupt_a_enable, 1);

		MDPRINTK("Interrupt_A_Enable_Register = 0x%04x\n",
			 devpriv->int_a_enable_reg);
	} else {
		/* interrupt on nothing */
		ni_set_bits(dev, Interrupt_A_Enable_Register, ~0, 0);

		/* XXX start polling if necessary */
		MDPRINTK("interrupting on nothing\n");
	}

	/* end configuration */
	devpriv->stc_writew(dev, AI_Configuration_End, Joint_Reset_Register);

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		devpriv->stc_writew(dev,
				    AI_SI2_Arm | AI_SI_Arm | AI_DIV_Arm |
				    AI_SC_Arm, AI_Command_1_Register);
		break;
	case TRIG_EXT:
		/* XXX AI_SI_Arm? */
		devpriv->stc_writew(dev,
				    AI_SI2_Arm | AI_SI_Arm | AI_DIV_Arm |
				    AI_SC_Arm, AI_Command_1_Register);
		break;
	}

#ifdef PCIDMA
	{
		int retval = ni_ai_setup_MITE_dma(dev);
		if (retval)
			return retval;
	}
	/* mite_dump_regs(devpriv->mite); */
#endif

	switch (cmd->start_src) {
	case TRIG_NOW:
		/* AI_START1_Pulse */
		devpriv->stc_writew(dev, AI_START1_Pulse | devpriv->ai_cmd2,
				    AI_Command_2_Register);
		s->async->inttrig = NULL;
		break;
	case TRIG_EXT:
		s->async->inttrig = NULL;
		break;
	case TRIG_INT:
		s->async->inttrig = &ni_ai_inttrig;
		break;
	}

	MDPRINTK("exit ni_ai_cmd\n");

	return 0;
}