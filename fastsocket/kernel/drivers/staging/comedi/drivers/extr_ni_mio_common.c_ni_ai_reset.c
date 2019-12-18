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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ reg_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CONVERT_Output_Enable_High ; 
 int /*<<< orphan*/  AI_CONVERT_Output_Enable_Low ; 
 unsigned int AI_CONVERT_Output_Select (int /*<<< orphan*/ ) ; 
 int AI_CONVERT_Pulse_Width ; 
 int /*<<< orphan*/  AI_Command_1_Register ; 
 int AI_Configuration_End ; 
 int AI_Configuration_Start ; 
 int AI_Disarm ; 
 unsigned int AI_EXTMUX_CLK_Output_Select (int /*<<< orphan*/ ) ; 
 int AI_Error_Interrupt_Ack ; 
 int AI_Error_Interrupt_Enable ; 
 int AI_FIFO_Interrupt_Enable ; 
 unsigned int AI_LOCALMUX_CLK_Output_Select (int) ; 
 int AI_LOCALMUX_CLK_Pulse_Width ; 
 int /*<<< orphan*/  AI_Mode_1_Register ; 
 int AI_Mode_1_Reserved ; 
 int /*<<< orphan*/  AI_Mode_2_Register ; 
 int /*<<< orphan*/  AI_Mode_3_Register ; 
 int /*<<< orphan*/  AI_Output_Control_Register ; 
 int /*<<< orphan*/  AI_Personal_Register ; 
 int AI_Reset ; 
 unsigned int AI_SCAN_IN_PROG_Output_Select (int) ; 
 int AI_SC_TC_Error_Confirm ; 
 int AI_SC_TC_Interrupt_Ack ; 
 int AI_SC_TC_Interrupt_Enable ; 
 unsigned int AI_SC_TC_Output_Select (int) ; 
 int AI_SHIFTIN_Pulse_Width ; 
 int AI_SOC_Polarity ; 
 int AI_START1_Interrupt_Ack ; 
 int AI_START1_Interrupt_Enable ; 
 int AI_START2_Interrupt_Ack ; 
 int AI_START2_Interrupt_Enable ; 
 int AI_START_Interrupt_Ack ; 
 int AI_START_Interrupt_Enable ; 
 int AI_STOP_Interrupt_Ack ; 
 int AI_STOP_Interrupt_Enable ; 
 int AI_Start_Stop ; 
 int /*<<< orphan*/  Interrupt_A_Ack_Register ; 
 int /*<<< orphan*/  Interrupt_A_Enable_Register ; 
 int /*<<< orphan*/  Joint_Reset_Register ; 
 int /*<<< orphan*/  Misc_Command ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_clear_ai_fifo (struct comedi_device*) ; 
 scalar_t__ ni_reg_611x ; 
 scalar_t__ ni_reg_6143 ; 
 scalar_t__ ni_reg_622x ; 
 int /*<<< orphan*/  ni_release_ai_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ai_reset(struct comedi_device *dev, struct comedi_subdevice *s)
{
	ni_release_ai_mite_channel(dev);
	/* ai configuration */
	devpriv->stc_writew(dev, AI_Configuration_Start | AI_Reset,
			    Joint_Reset_Register);

	ni_set_bits(dev, Interrupt_A_Enable_Register,
		    AI_SC_TC_Interrupt_Enable | AI_START1_Interrupt_Enable |
		    AI_START2_Interrupt_Enable | AI_START_Interrupt_Enable |
		    AI_STOP_Interrupt_Enable | AI_Error_Interrupt_Enable |
		    AI_FIFO_Interrupt_Enable, 0);

	ni_clear_ai_fifo(dev);

	if (boardtype.reg_type != ni_reg_6143)
		ni_writeb(0, Misc_Command);

	devpriv->stc_writew(dev, AI_Disarm, AI_Command_1_Register);	/* reset pulses */
	devpriv->stc_writew(dev,
			    AI_Start_Stop | AI_Mode_1_Reserved
			    /*| AI_Trigger_Once */ ,
			    AI_Mode_1_Register);
	devpriv->stc_writew(dev, 0x0000, AI_Mode_2_Register);
	/* generate FIFO interrupts on non-empty */
	devpriv->stc_writew(dev, (0 << 6) | 0x0000, AI_Mode_3_Register);
	if (boardtype.reg_type == ni_reg_611x) {
		devpriv->stc_writew(dev, AI_SHIFTIN_Pulse_Width |
				    AI_SOC_Polarity |
				    AI_LOCALMUX_CLK_Pulse_Width,
				    AI_Personal_Register);
		devpriv->stc_writew(dev,
				    AI_SCAN_IN_PROG_Output_Select(3) |
				    AI_EXTMUX_CLK_Output_Select(0) |
				    AI_LOCALMUX_CLK_Output_Select(2) |
				    AI_SC_TC_Output_Select(3) |
				    AI_CONVERT_Output_Select
				    (AI_CONVERT_Output_Enable_High),
				    AI_Output_Control_Register);
	} else if (boardtype.reg_type == ni_reg_6143) {
		devpriv->stc_writew(dev, AI_SHIFTIN_Pulse_Width |
				    AI_SOC_Polarity |
				    AI_LOCALMUX_CLK_Pulse_Width,
				    AI_Personal_Register);
		devpriv->stc_writew(dev,
				    AI_SCAN_IN_PROG_Output_Select(3) |
				    AI_EXTMUX_CLK_Output_Select(0) |
				    AI_LOCALMUX_CLK_Output_Select(2) |
				    AI_SC_TC_Output_Select(3) |
				    AI_CONVERT_Output_Select
				    (AI_CONVERT_Output_Enable_Low),
				    AI_Output_Control_Register);
	} else {
		unsigned ai_output_control_bits;
		devpriv->stc_writew(dev, AI_SHIFTIN_Pulse_Width |
				    AI_SOC_Polarity |
				    AI_CONVERT_Pulse_Width |
				    AI_LOCALMUX_CLK_Pulse_Width,
				    AI_Personal_Register);
		ai_output_control_bits =
		    AI_SCAN_IN_PROG_Output_Select(3) |
		    AI_EXTMUX_CLK_Output_Select(0) |
		    AI_LOCALMUX_CLK_Output_Select(2) |
		    AI_SC_TC_Output_Select(3);
		if (boardtype.reg_type == ni_reg_622x)
			ai_output_control_bits |=
			    AI_CONVERT_Output_Select
			    (AI_CONVERT_Output_Enable_High);
		else
			ai_output_control_bits |=
			    AI_CONVERT_Output_Select
			    (AI_CONVERT_Output_Enable_Low);
		devpriv->stc_writew(dev, ai_output_control_bits,
				    AI_Output_Control_Register);
	}
	/* the following registers should not be changed, because there
	 * are no backup registers in devpriv.  If you want to change
	 * any of these, add a backup register and other appropriate code:
	 *      AI_Mode_1_Register
	 *      AI_Mode_3_Register
	 *      AI_Personal_Register
	 *      AI_Output_Control_Register
	 */
	devpriv->stc_writew(dev, AI_SC_TC_Error_Confirm | AI_START_Interrupt_Ack | AI_START2_Interrupt_Ack | AI_START1_Interrupt_Ack | AI_SC_TC_Interrupt_Ack | AI_Error_Interrupt_Ack | AI_STOP_Interrupt_Ack, Interrupt_A_Ack_Register);	/* clear interrupts */

	devpriv->stc_writew(dev, AI_Configuration_End, Joint_Reset_Register);

	return 0;
}