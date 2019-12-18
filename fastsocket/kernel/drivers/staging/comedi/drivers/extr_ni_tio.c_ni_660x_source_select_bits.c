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
 int Gi_Source_Select_Bits (unsigned int) ; 
 unsigned int NI_660x_Logic_Low_Clock ; 
 unsigned int NI_660x_Next_Gate_Clock ; 
 unsigned int NI_660x_Next_TC_Clock ; 
 unsigned int NI_660x_RTSI_Clock (unsigned int) ; 
 unsigned int NI_660x_Source_Pin_Clock (unsigned int) ; 
 unsigned int NI_660x_Source_Pin_i_Clock ; 
 unsigned int NI_660x_Timebase_1_Clock ; 
 unsigned int NI_660x_Timebase_2_Clock ; 
 unsigned int NI_660x_Timebase_3_Clock ; 
 unsigned int NI_GPCT_CLOCK_SRC_SELECT_MASK ; 
#define  NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS 134 
#define  NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS 133 
#define  NI_GPCT_NEXT_TC_CLOCK_SRC_BITS 132 
 unsigned int const NI_GPCT_RTSI_CLOCK_SRC_BITS (unsigned int) ; 
 unsigned int const NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS (unsigned int) ; 
#define  NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS 131 
#define  NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS 130 
#define  NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS 129 
#define  NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS 128 
 unsigned int ni_660x_max_rtsi_channel ; 
 unsigned int ni_660x_max_source_pin ; 

__attribute__((used)) static unsigned ni_660x_source_select_bits(unsigned int clock_source)
{
	unsigned ni_660x_clock;
	unsigned i;
	const unsigned clock_select_bits =
	    clock_source & NI_GPCT_CLOCK_SRC_SELECT_MASK;

	switch (clock_select_bits) {
	case NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Timebase_1_Clock;
		break;
	case NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Timebase_2_Clock;
		break;
	case NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Timebase_3_Clock;
		break;
	case NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Logic_Low_Clock;
		break;
	case NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Source_Pin_i_Clock;
		break;
	case NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Next_Gate_Clock;
		break;
	case NI_GPCT_NEXT_TC_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660x_Next_TC_Clock;
		break;
	default:
		for (i = 0; i <= ni_660x_max_rtsi_channel; ++i) {
			if (clock_select_bits == NI_GPCT_RTSI_CLOCK_SRC_BITS(i)) {
				ni_660x_clock = NI_660x_RTSI_Clock(i);
				break;
			}
		}
		if (i <= ni_660x_max_rtsi_channel)
			break;
		for (i = 0; i <= ni_660x_max_source_pin; ++i) {
			if (clock_select_bits ==
			    NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS(i)) {
				ni_660x_clock = NI_660x_Source_Pin_Clock(i);
				break;
			}
		}
		if (i <= ni_660x_max_source_pin)
			break;
		ni_660x_clock = 0;
		BUG();
		break;
	}
	return Gi_Source_Select_Bits(ni_660x_clock);
}