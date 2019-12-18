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
struct comedi_cmd {int chanlist_len; int* chanlist; int stop_src; int start_src; int start_arg; int stop_arg; int scan_begin_src; int scan_begin_arg; int scan_end_arg; } ;
struct TYPE_6__ {int reg_type; scalar_t__ ao_fifo_depth; } ;
struct TYPE_5__ {int ao_mode1; int ao_trigger_select; int ao_mode3; int ao_mode2; int ao_cmd2; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stc_writel ) (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int AO_AOFREQ_Enable ; 
 int AO_BC_Gate_Enable ; 
 int AO_BC_Initial_Load_Source ; 
 int AO_BC_Load ; 
 int /*<<< orphan*/  AO_BC_Load_A_Register ; 
 int AO_BC_Source_Select ; 
 int AO_BC_TC_Interrupt_Ack ; 
 int /*<<< orphan*/  AO_BC_TC_Interrupt_Enable ; 
 int /*<<< orphan*/  AO_Command_1_Register ; 
 int /*<<< orphan*/  AO_Command_2_Register ; 
 int AO_Configuration_End ; 
 int AO_Configuration_Start ; 
 int AO_Continuous ; 
 int AO_DAC0_Update_Mode ; 
 int AO_DAC1_Update_Mode ; 
 int AO_DMA_PIO_Control ; 
 int AO_Disarm ; 
 int AO_FIFO_Enable ; 
 int AO_FIFO_Mode_HF ; 
 int AO_FIFO_Mode_HF_to_F ; 
 int AO_FIFO_Mode_Mask ; 
 int AO_FIFO_Retransmit_Enable ; 
 int /*<<< orphan*/  AO_Misc_611x ; 
 int /*<<< orphan*/  AO_Mode_1_Register ; 
 int /*<<< orphan*/  AO_Mode_2_Register ; 
 int /*<<< orphan*/  AO_Mode_3_Register ; 
 int AO_Multiple_Channels ; 
 unsigned int AO_Number_Of_Channels (int) ; 
 int AO_Number_Of_DAC_Packages ; 
 int /*<<< orphan*/  AO_Output_Control_Register ; 
 int /*<<< orphan*/  AO_Personal_Register ; 
 int AO_START1_Edge ; 
 int AO_START1_Polarity ; 
 int AO_START1_Select (int) ; 
 int AO_START1_Sync ; 
 int /*<<< orphan*/  AO_Start_Select_Register ; 
 int AO_Stop_On_Overrun_Error ; 
 int AO_TMRDACWR_Pulse_Width ; 
 int /*<<< orphan*/  AO_Timed_611x ; 
 int AO_Trigger_Length ; 
 int AO_Trigger_Once ; 
 int /*<<< orphan*/  AO_Trigger_Select_Register ; 
 int AO_UC_Initial_Load_Source ; 
 int AO_UC_Load ; 
 int /*<<< orphan*/  AO_UC_Load_A_Register ; 
 int AO_UI_Initial_Load_Source ; 
 int AO_UI_Load ; 
 int /*<<< orphan*/  AO_UI_Load_A_Register ; 
 int AO_UI_Reload_Mode (int) ; 
 int AO_UI_Source_Polarity ; 
 int AO_UI_Source_Select (int) ; 
 unsigned int AO_UPDATE_Output_Select (int /*<<< orphan*/ ) ; 
 int AO_UPDATE_Pulse_Width ; 
 int AO_UPDATE_Source_Polarity ; 
 int AO_UPDATE_Source_Select (int) ; 
 int /*<<< orphan*/  AO_Update_Output_High_Z ; 
 int /*<<< orphan*/  AO_Waveform_Generation_611x ; 
 int /*<<< orphan*/  BUG () ; 
 int CLEAR_WG ; 
 int CR_CHAN (int) ; 
 int CR_EDGE ; 
 int CR_INVERT ; 
 int EIO ; 
 int /*<<< orphan*/  Interrupt_B_Ack_Register ; 
 int /*<<< orphan*/  Interrupt_B_Enable_Register ; 
 int /*<<< orphan*/  Joint_Reset_Register ; 
#define  TRIG_COUNT 133 
#define  TRIG_EXT 132 
#define  TRIG_INT 131 
#define  TRIG_NONE 130 
#define  TRIG_NOW 129 
 int /*<<< orphan*/  TRIG_ROUND_NEAREST ; 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  ao_win_out (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ boardtype ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  ni_ao_config_chanlist (struct comedi_device*,struct comedi_subdevice*,int*,int,int) ; 
 int /*<<< orphan*/  ni_ao_inttrig ; 
 unsigned int ni_ns_to_timer (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int ni_reg_6xxx_mask ; 
 int ni_reg_m_series_mask ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub24 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub27 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub28 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub29 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub30 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub31 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub32 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub33 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub34 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub35 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub36 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub37 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub38 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub39 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	const struct comedi_cmd *cmd = &s->async->cmd;
	int bits;
	int i;
	unsigned trigvar;

	if (dev->irq == 0) {
		comedi_error(dev, "cannot run command without an irq");
		return -EIO;
	}

	devpriv->stc_writew(dev, AO_Configuration_Start, Joint_Reset_Register);

	devpriv->stc_writew(dev, AO_Disarm, AO_Command_1_Register);

	if (boardtype.reg_type & ni_reg_6xxx_mask) {
		ao_win_out(CLEAR_WG, AO_Misc_611x);

		bits = 0;
		for (i = 0; i < cmd->chanlist_len; i++) {
			int chan;

			chan = CR_CHAN(cmd->chanlist[i]);
			bits |= 1 << chan;
			ao_win_out(chan, AO_Waveform_Generation_611x);
		}
		ao_win_out(bits, AO_Timed_611x);
	}

	ni_ao_config_chanlist(dev, s, cmd->chanlist, cmd->chanlist_len, 1);

	if (cmd->stop_src == TRIG_NONE) {
		devpriv->ao_mode1 |= AO_Continuous;
		devpriv->ao_mode1 &= ~AO_Trigger_Once;
	} else {
		devpriv->ao_mode1 &= ~AO_Continuous;
		devpriv->ao_mode1 |= AO_Trigger_Once;
	}
	devpriv->stc_writew(dev, devpriv->ao_mode1, AO_Mode_1_Register);
	switch (cmd->start_src) {
	case TRIG_INT:
	case TRIG_NOW:
		devpriv->ao_trigger_select &=
		    ~(AO_START1_Polarity | AO_START1_Select(-1));
		devpriv->ao_trigger_select |= AO_START1_Edge | AO_START1_Sync;
		devpriv->stc_writew(dev, devpriv->ao_trigger_select,
				    AO_Trigger_Select_Register);
		break;
	case TRIG_EXT:
		devpriv->ao_trigger_select =
		    AO_START1_Select(CR_CHAN(cmd->start_arg) + 1);
		if (cmd->start_arg & CR_INVERT)
			devpriv->ao_trigger_select |= AO_START1_Polarity;	/*  0=active high, 1=active low. see daq-stc 3-24 (p186) */
		if (cmd->start_arg & CR_EDGE)
			devpriv->ao_trigger_select |= AO_START1_Edge;	/*  0=edge detection disabled, 1=enabled */
		devpriv->stc_writew(dev, devpriv->ao_trigger_select,
				    AO_Trigger_Select_Register);
		break;
	default:
		BUG();
		break;
	}
	devpriv->ao_mode3 &= ~AO_Trigger_Length;
	devpriv->stc_writew(dev, devpriv->ao_mode3, AO_Mode_3_Register);

	devpriv->stc_writew(dev, devpriv->ao_mode1, AO_Mode_1_Register);
	devpriv->ao_mode2 &= ~AO_BC_Initial_Load_Source;
	devpriv->stc_writew(dev, devpriv->ao_mode2, AO_Mode_2_Register);
	if (cmd->stop_src == TRIG_NONE) {
		devpriv->stc_writel(dev, 0xffffff, AO_BC_Load_A_Register);
	} else {
		devpriv->stc_writel(dev, 0, AO_BC_Load_A_Register);
	}
	devpriv->stc_writew(dev, AO_BC_Load, AO_Command_1_Register);
	devpriv->ao_mode2 &= ~AO_UC_Initial_Load_Source;
	devpriv->stc_writew(dev, devpriv->ao_mode2, AO_Mode_2_Register);
	switch (cmd->stop_src) {
	case TRIG_COUNT:
		if (boardtype.reg_type & ni_reg_m_series_mask) {
			/*  this is how the NI example code does it for m-series boards, verified correct with 6259 */
			devpriv->stc_writel(dev, cmd->stop_arg - 1,
					    AO_UC_Load_A_Register);
			devpriv->stc_writew(dev, AO_UC_Load,
					    AO_Command_1_Register);
		} else {
			devpriv->stc_writel(dev, cmd->stop_arg,
					    AO_UC_Load_A_Register);
			devpriv->stc_writew(dev, AO_UC_Load,
					    AO_Command_1_Register);
			devpriv->stc_writel(dev, cmd->stop_arg - 1,
					    AO_UC_Load_A_Register);
		}
		break;
	case TRIG_NONE:
		devpriv->stc_writel(dev, 0xffffff, AO_UC_Load_A_Register);
		devpriv->stc_writew(dev, AO_UC_Load, AO_Command_1_Register);
		devpriv->stc_writel(dev, 0xffffff, AO_UC_Load_A_Register);
		break;
	default:
		devpriv->stc_writel(dev, 0, AO_UC_Load_A_Register);
		devpriv->stc_writew(dev, AO_UC_Load, AO_Command_1_Register);
		devpriv->stc_writel(dev, cmd->stop_arg, AO_UC_Load_A_Register);
	}

	devpriv->ao_mode1 &=
	    ~(AO_UI_Source_Select(0x1f) | AO_UI_Source_Polarity |
	      AO_UPDATE_Source_Select(0x1f) | AO_UPDATE_Source_Polarity);
	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		devpriv->ao_cmd2 &= ~AO_BC_Gate_Enable;
		trigvar =
		    ni_ns_to_timer(dev, cmd->scan_begin_arg,
				   TRIG_ROUND_NEAREST);
		devpriv->stc_writel(dev, 1, AO_UI_Load_A_Register);
		devpriv->stc_writew(dev, AO_UI_Load, AO_Command_1_Register);
		devpriv->stc_writel(dev, trigvar, AO_UI_Load_A_Register);
		break;
	case TRIG_EXT:
		devpriv->ao_mode1 |=
		    AO_UPDATE_Source_Select(cmd->scan_begin_arg);
		if (cmd->scan_begin_arg & CR_INVERT)
			devpriv->ao_mode1 |= AO_UPDATE_Source_Polarity;
		devpriv->ao_cmd2 |= AO_BC_Gate_Enable;
		break;
	default:
		BUG();
		break;
	}
	devpriv->stc_writew(dev, devpriv->ao_cmd2, AO_Command_2_Register);
	devpriv->stc_writew(dev, devpriv->ao_mode1, AO_Mode_1_Register);
	devpriv->ao_mode2 &=
	    ~(AO_UI_Reload_Mode(3) | AO_UI_Initial_Load_Source);
	devpriv->stc_writew(dev, devpriv->ao_mode2, AO_Mode_2_Register);

	if (cmd->scan_end_arg > 1) {
		devpriv->ao_mode1 |= AO_Multiple_Channels;
		devpriv->stc_writew(dev,
				    AO_Number_Of_Channels(cmd->scan_end_arg -
							  1) |
				    AO_UPDATE_Output_Select
				    (AO_Update_Output_High_Z),
				    AO_Output_Control_Register);
	} else {
		unsigned bits;
		devpriv->ao_mode1 &= ~AO_Multiple_Channels;
		bits = AO_UPDATE_Output_Select(AO_Update_Output_High_Z);
		if (boardtype.
		    reg_type & (ni_reg_m_series_mask | ni_reg_6xxx_mask)) {
			bits |= AO_Number_Of_Channels(0);
		} else {
			bits |=
			    AO_Number_Of_Channels(CR_CHAN(cmd->chanlist[0]));
		}
		devpriv->stc_writew(dev, bits, AO_Output_Control_Register);
	}
	devpriv->stc_writew(dev, devpriv->ao_mode1, AO_Mode_1_Register);

	devpriv->stc_writew(dev, AO_DAC0_Update_Mode | AO_DAC1_Update_Mode,
			    AO_Command_1_Register);

	devpriv->ao_mode3 |= AO_Stop_On_Overrun_Error;
	devpriv->stc_writew(dev, devpriv->ao_mode3, AO_Mode_3_Register);

	devpriv->ao_mode2 &= ~AO_FIFO_Mode_Mask;
#ifdef PCIDMA
	devpriv->ao_mode2 |= AO_FIFO_Mode_HF_to_F;
#else
	devpriv->ao_mode2 |= AO_FIFO_Mode_HF;
#endif
	devpriv->ao_mode2 &= ~AO_FIFO_Retransmit_Enable;
	devpriv->stc_writew(dev, devpriv->ao_mode2, AO_Mode_2_Register);

	bits = AO_BC_Source_Select | AO_UPDATE_Pulse_Width |
	    AO_TMRDACWR_Pulse_Width;
	if (boardtype.ao_fifo_depth)
		bits |= AO_FIFO_Enable;
	else
		bits |= AO_DMA_PIO_Control;
#if 0
	/* F Hess: windows driver does not set AO_Number_Of_DAC_Packages bit for 6281,
	   verified with bus analyzer. */
	if (boardtype.reg_type & ni_reg_m_series_mask)
		bits |= AO_Number_Of_DAC_Packages;
#endif
	devpriv->stc_writew(dev, bits, AO_Personal_Register);
	/*  enable sending of ao dma requests */
	devpriv->stc_writew(dev, AO_AOFREQ_Enable, AO_Start_Select_Register);

	devpriv->stc_writew(dev, AO_Configuration_End, Joint_Reset_Register);

	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->stc_writew(dev, AO_BC_TC_Interrupt_Ack,
				    Interrupt_B_Ack_Register);
		ni_set_bits(dev, Interrupt_B_Enable_Register,
			    AO_BC_TC_Interrupt_Enable, 1);
	}

	s->async->inttrig = &ni_ao_inttrig;

	return 0;
}