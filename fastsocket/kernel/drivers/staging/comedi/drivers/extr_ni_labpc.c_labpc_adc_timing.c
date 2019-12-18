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
struct comedi_device {int dummy; } ;
struct comedi_cmd {int flags; } ;
struct TYPE_2__ {int divisor_b0; unsigned int divisor_a0; unsigned int divisor_b1; } ;

/* Variables and functions */
 int const LABPC_TIMER_BASE ; 
#define  TRIG_ROUND_DOWN 130 
 int TRIG_ROUND_MASK ; 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int const,unsigned int*,int const*,unsigned int*,int) ; 
 int labpc_ai_convert_period (struct comedi_cmd*) ; 
 int labpc_ai_scan_period (struct comedi_cmd*) ; 
 int /*<<< orphan*/  labpc_set_ai_convert_period (struct comedi_cmd*,unsigned int) ; 
 int /*<<< orphan*/  labpc_set_ai_scan_period (struct comedi_cmd*,unsigned int) ; 

__attribute__((used)) static void labpc_adc_timing(struct comedi_device *dev, struct comedi_cmd *cmd)
{
	const int max_counter_value = 0x10000;	/*  max value for 16 bit counter in mode 2 */
	const int min_counter_value = 2;	/*  min value for 16 bit counter in mode 2 */
	unsigned int base_period;

	/*  if both convert and scan triggers are TRIG_TIMER, then they both rely on counter b0 */
	if (labpc_ai_convert_period(cmd) && labpc_ai_scan_period(cmd)) {
		/*  pick the lowest b0 divisor value we can (for maximum input clock speed on convert and scan counters) */
		devpriv->divisor_b0 = (labpc_ai_scan_period(cmd) - 1) /
		    (LABPC_TIMER_BASE * max_counter_value) + 1;
		if (devpriv->divisor_b0 < min_counter_value)
			devpriv->divisor_b0 = min_counter_value;
		if (devpriv->divisor_b0 > max_counter_value)
			devpriv->divisor_b0 = max_counter_value;

		base_period = LABPC_TIMER_BASE * devpriv->divisor_b0;

		/*  set a0 for conversion frequency and b1 for scan frequency */
		switch (cmd->flags & TRIG_ROUND_MASK) {
		default:
		case TRIG_ROUND_NEAREST:
			devpriv->divisor_a0 =
			    (labpc_ai_convert_period(cmd) +
			     (base_period / 2)) / base_period;
			devpriv->divisor_b1 =
			    (labpc_ai_scan_period(cmd) +
			     (base_period / 2)) / base_period;
			break;
		case TRIG_ROUND_UP:
			devpriv->divisor_a0 =
			    (labpc_ai_convert_period(cmd) + (base_period -
							     1)) / base_period;
			devpriv->divisor_b1 =
			    (labpc_ai_scan_period(cmd) + (base_period -
							  1)) / base_period;
			break;
		case TRIG_ROUND_DOWN:
			devpriv->divisor_a0 =
			    labpc_ai_convert_period(cmd) / base_period;
			devpriv->divisor_b1 =
			    labpc_ai_scan_period(cmd) / base_period;
			break;
		}
		/*  make sure a0 and b1 values are acceptable */
		if (devpriv->divisor_a0 < min_counter_value)
			devpriv->divisor_a0 = min_counter_value;
		if (devpriv->divisor_a0 > max_counter_value)
			devpriv->divisor_a0 = max_counter_value;
		if (devpriv->divisor_b1 < min_counter_value)
			devpriv->divisor_b1 = min_counter_value;
		if (devpriv->divisor_b1 > max_counter_value)
			devpriv->divisor_b1 = max_counter_value;
		/*  write corrected timings to command */
		labpc_set_ai_convert_period(cmd,
					    base_period * devpriv->divisor_a0);
		labpc_set_ai_scan_period(cmd,
					 base_period * devpriv->divisor_b1);
		/*  if only one TRIG_TIMER is used, we can employ the generic cascaded timing functions */
	} else if (labpc_ai_scan_period(cmd)) {
		unsigned int scan_period;

		scan_period = labpc_ai_scan_period(cmd);
		/* calculate cascaded counter values that give desired scan timing */
		i8253_cascade_ns_to_timer_2div(LABPC_TIMER_BASE,
					       &(devpriv->divisor_b1),
					       &(devpriv->divisor_b0),
					       &scan_period,
					       cmd->flags & TRIG_ROUND_MASK);
		labpc_set_ai_scan_period(cmd, scan_period);
	} else if (labpc_ai_convert_period(cmd)) {
		unsigned int convert_period;

		convert_period = labpc_ai_convert_period(cmd);
		/* calculate cascaded counter values that give desired conversion timing */
		i8253_cascade_ns_to_timer_2div(LABPC_TIMER_BASE,
					       &(devpriv->divisor_a0),
					       &(devpriv->divisor_b0),
					       &convert_period,
					       cmd->flags & TRIG_ROUND_MASK);
		labpc_set_ai_convert_period(cmd, convert_period);
	}
}