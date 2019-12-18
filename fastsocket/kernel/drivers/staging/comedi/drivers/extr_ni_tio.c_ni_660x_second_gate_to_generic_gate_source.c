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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  NI_660x_Logic_Low_Second_Gate_Select 133 
#define  NI_660x_Next_Out_Second_Gate_Select 132 
#define  NI_660x_Next_SRC_Second_Gate_Select 131 
 unsigned int NI_660x_RTSI_Second_Gate_Select (unsigned int) ; 
#define  NI_660x_Selected_Gate_Second_Gate_Select 130 
#define  NI_660x_Source_Pin_i_Second_Gate_Select 129 
 unsigned int NI_660x_Up_Down_Pin_Second_Gate_Select (unsigned int) ; 
#define  NI_660x_Up_Down_Pin_i_Second_Gate_Select 128 
 int NI_GPCT_LOGIC_LOW_GATE_SELECT ; 
 int NI_GPCT_NEXT_OUT_GATE_SELECT ; 
 int NI_GPCT_NEXT_SOURCE_GATE_SELECT ; 
 int NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
 int NI_GPCT_SELECTED_GATE_GATE_SELECT ; 
 int NI_GPCT_SOURCE_PIN_i_GATE_SELECT ; 
 int NI_GPCT_UP_DOWN_PIN_GATE_SELECT (unsigned int) ; 
 int NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT ; 
 unsigned int ni_660x_max_rtsi_channel ; 
 unsigned int ni_660x_max_up_down_pin ; 

__attribute__((used)) static unsigned ni_660x_second_gate_to_generic_gate_source(unsigned
							   ni_660x_gate_select)
{
	unsigned i;

	switch (ni_660x_gate_select) {
	case NI_660x_Source_Pin_i_Second_Gate_Select:
		return NI_GPCT_SOURCE_PIN_i_GATE_SELECT;
		break;
	case NI_660x_Up_Down_Pin_i_Second_Gate_Select:
		return NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT;
		break;
	case NI_660x_Next_SRC_Second_Gate_Select:
		return NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		break;
	case NI_660x_Next_Out_Second_Gate_Select:
		return NI_GPCT_NEXT_OUT_GATE_SELECT;
		break;
	case NI_660x_Selected_Gate_Second_Gate_Select:
		return NI_GPCT_SELECTED_GATE_GATE_SELECT;
		break;
	case NI_660x_Logic_Low_Second_Gate_Select:
		return NI_GPCT_LOGIC_LOW_GATE_SELECT;
		break;
	default:
		for (i = 0; i <= ni_660x_max_rtsi_channel; ++i) {
			if (ni_660x_gate_select ==
			    NI_660x_RTSI_Second_Gate_Select(i)) {
				return NI_GPCT_RTSI_GATE_SELECT(i);
				break;
			}
		}
		if (i <= ni_660x_max_rtsi_channel)
			break;
		for (i = 0; i <= ni_660x_max_up_down_pin; ++i) {
			if (ni_660x_gate_select ==
			    NI_660x_Up_Down_Pin_Second_Gate_Select(i)) {
				return NI_GPCT_UP_DOWN_PIN_GATE_SELECT(i);
				break;
			}
		}
		if (i <= ni_660x_max_up_down_pin)
			break;
		BUG();
		break;
	}
	return 0;
}