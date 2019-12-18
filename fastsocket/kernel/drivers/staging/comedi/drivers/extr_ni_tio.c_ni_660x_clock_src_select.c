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
struct ni_gpct {int /*<<< orphan*/  counter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int Gi_Source_Select_Mask ; 
 unsigned int Gi_Source_Select_Shift ; 
 int /*<<< orphan*/  NITIO_Gi_Input_Select_Reg (int /*<<< orphan*/ ) ; 
#define  NI_660x_Logic_Low_Clock 134 
#define  NI_660x_Next_Gate_Clock 133 
#define  NI_660x_Next_TC_Clock 132 
 unsigned int const NI_660x_RTSI_Clock (unsigned int) ; 
 unsigned int const NI_660x_Source_Pin_Clock (unsigned int) ; 
#define  NI_660x_Source_Pin_i_Clock 131 
#define  NI_660x_Timebase_1_Clock 130 
#define  NI_660x_Timebase_2_Clock 129 
#define  NI_660x_Timebase_3_Clock 128 
 unsigned int NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_NEXT_TC_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_RTSI_CLOCK_SRC_BITS (unsigned int) ; 
 unsigned int NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS (unsigned int) ; 
 unsigned int NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS ; 
 unsigned int ni_660x_max_rtsi_channel ; 
 unsigned int ni_660x_max_source_pin ; 
 unsigned int ni_tio_clock_src_modifiers (struct ni_gpct const*) ; 
 unsigned int ni_tio_get_soft_copy (struct ni_gpct const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned ni_660x_clock_src_select(const struct ni_gpct *counter)
{
	unsigned clock_source = 0;
	unsigned i;
	const unsigned input_select = (ni_tio_get_soft_copy(counter,
							    NITIO_Gi_Input_Select_Reg
							    (counter->counter_index))
				       & Gi_Source_Select_Mask) >>
	    Gi_Source_Select_Shift;

	switch (input_select) {
	case NI_660x_Timebase_1_Clock:
		clock_source = NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS;
		break;
	case NI_660x_Timebase_2_Clock:
		clock_source = NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS;
		break;
	case NI_660x_Timebase_3_Clock:
		clock_source = NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS;
		break;
	case NI_660x_Logic_Low_Clock:
		clock_source = NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS;
		break;
	case NI_660x_Source_Pin_i_Clock:
		clock_source = NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS;
		break;
	case NI_660x_Next_Gate_Clock:
		clock_source = NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS;
		break;
	case NI_660x_Next_TC_Clock:
		clock_source = NI_GPCT_NEXT_TC_CLOCK_SRC_BITS;
		break;
	default:
		for (i = 0; i <= ni_660x_max_rtsi_channel; ++i) {
			if (input_select == NI_660x_RTSI_Clock(i)) {
				clock_source = NI_GPCT_RTSI_CLOCK_SRC_BITS(i);
				break;
			}
		}
		if (i <= ni_660x_max_rtsi_channel)
			break;
		for (i = 0; i <= ni_660x_max_source_pin; ++i) {
			if (input_select == NI_660x_Source_Pin_Clock(i)) {
				clock_source =
				    NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS(i);
				break;
			}
		}
		if (i <= ni_660x_max_source_pin)
			break;
		BUG();
		break;
	}
	clock_source |= ni_tio_clock_src_modifiers(counter);
	return clock_source;
}