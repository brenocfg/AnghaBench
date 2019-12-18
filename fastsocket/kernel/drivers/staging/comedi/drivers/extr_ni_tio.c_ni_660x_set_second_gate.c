#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ni_gpct_device {int /*<<< orphan*/ * regs; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  Gi_Second_Gate_Mode_Bit ; 
 int /*<<< orphan*/  Gi_Second_Gate_Select_Bits (unsigned int) ; 
 int /*<<< orphan*/  Gi_Second_Gate_Select_Mask ; 
 unsigned int NITIO_Gi_Second_Gate_Reg (int /*<<< orphan*/ ) ; 
 unsigned int NI_660x_Next_SRC_Second_Gate_Select ; 
#define  NI_GPCT_LOGIC_LOW_GATE_SELECT 133 
#define  NI_GPCT_NEXT_OUT_GATE_SELECT 132 
#define  NI_GPCT_NEXT_SOURCE_GATE_SELECT 131 
 unsigned int const NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
#define  NI_GPCT_SELECTED_GATE_GATE_SELECT 130 
#define  NI_GPCT_SOURCE_PIN_i_GATE_SELECT 129 
 unsigned int const NI_GPCT_UP_DOWN_PIN_GATE_SELECT (unsigned int) ; 
#define  NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT 128 
 unsigned int ni_660x_max_rtsi_channel ; 
 unsigned int ni_660x_max_up_down_pin ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int const) ; 

__attribute__((used)) static int ni_660x_set_second_gate(struct ni_gpct *counter,
				   unsigned int gate_source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const unsigned second_gate_reg =
	    NITIO_Gi_Second_Gate_Reg(counter->counter_index);
	const unsigned selected_second_gate = CR_CHAN(gate_source);
	/* bits of second_gate that may be meaningful to second gate register */
	static const unsigned selected_second_gate_mask = 0x1f;
	unsigned ni_660x_second_gate_select;
	unsigned i;

	switch (selected_second_gate) {
	case NI_GPCT_SOURCE_PIN_i_GATE_SELECT:
	case NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT:
	case NI_GPCT_SELECTED_GATE_GATE_SELECT:
	case NI_GPCT_NEXT_OUT_GATE_SELECT:
	case NI_GPCT_LOGIC_LOW_GATE_SELECT:
		ni_660x_second_gate_select =
		    selected_second_gate & selected_second_gate_mask;
		break;
	case NI_GPCT_NEXT_SOURCE_GATE_SELECT:
		ni_660x_second_gate_select =
		    NI_660x_Next_SRC_Second_Gate_Select;
		break;
	default:
		for (i = 0; i <= ni_660x_max_rtsi_channel; ++i) {
			if (selected_second_gate == NI_GPCT_RTSI_GATE_SELECT(i)) {
				ni_660x_second_gate_select =
				    selected_second_gate &
				    selected_second_gate_mask;
				break;
			}
		}
		if (i <= ni_660x_max_rtsi_channel)
			break;
		for (i = 0; i <= ni_660x_max_up_down_pin; ++i) {
			if (selected_second_gate ==
			    NI_GPCT_UP_DOWN_PIN_GATE_SELECT(i)) {
				ni_660x_second_gate_select =
				    selected_second_gate &
				    selected_second_gate_mask;
				break;
			}
		}
		if (i <= ni_660x_max_up_down_pin)
			break;
		return -EINVAL;
		break;
	};
	counter_dev->regs[second_gate_reg] |= Gi_Second_Gate_Mode_Bit;
	counter_dev->regs[second_gate_reg] &= ~Gi_Second_Gate_Select_Mask;
	counter_dev->regs[second_gate_reg] |=
	    Gi_Second_Gate_Select_Bits(ni_660x_second_gate_select);
	write_register(counter, counter_dev->regs[second_gate_reg],
		       second_gate_reg);
	return 0;
}