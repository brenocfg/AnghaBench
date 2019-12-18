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
 int NI_GPCT_AI_START1_GATE_SELECT ; 
 int NI_GPCT_AI_START2_GATE_SELECT ; 
 int NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT ; 
 int NI_GPCT_LOGIC_LOW_GATE_SELECT ; 
 int NI_GPCT_NEXT_OUT_GATE_SELECT ; 
 int NI_GPCT_NEXT_SOURCE_GATE_SELECT ; 
 int NI_GPCT_PFI_GATE_SELECT (unsigned int) ; 
 int NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT ; 
 int NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
 int NI_GPCT_TIMESTAMP_MUX_GATE_SELECT ; 
#define  NI_M_Series_AI_START1_Gate_Select 135 
#define  NI_M_Series_AI_START2_Gate_Select 134 
#define  NI_M_Series_Analog_Trigger_Out_Gate_Select 133 
#define  NI_M_Series_Logic_Low_Gate_Select 132 
#define  NI_M_Series_Next_Out_Gate_Select 131 
#define  NI_M_Series_Next_SRC_Gate_Select 130 
 unsigned int NI_M_Series_PFI_Gate_Select (unsigned int) ; 
#define  NI_M_Series_PXI_Star_Trigger_Gate_Select 129 
 unsigned int NI_M_Series_RTSI_Gate_Select (unsigned int) ; 
#define  NI_M_Series_Timestamp_Mux_Gate_Select 128 
 unsigned int ni_m_series_max_pfi_channel ; 
 unsigned int ni_m_series_max_rtsi_channel ; 

__attribute__((used)) static unsigned ni_m_series_first_gate_to_generic_gate_source(unsigned
							      ni_m_series_gate_select)
{
	unsigned i;

	switch (ni_m_series_gate_select) {
	case NI_M_Series_Timestamp_Mux_Gate_Select:
		return NI_GPCT_TIMESTAMP_MUX_GATE_SELECT;
		break;
	case NI_M_Series_AI_START2_Gate_Select:
		return NI_GPCT_AI_START2_GATE_SELECT;
		break;
	case NI_M_Series_PXI_Star_Trigger_Gate_Select:
		return NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT;
		break;
	case NI_M_Series_Next_Out_Gate_Select:
		return NI_GPCT_NEXT_OUT_GATE_SELECT;
		break;
	case NI_M_Series_AI_START1_Gate_Select:
		return NI_GPCT_AI_START1_GATE_SELECT;
		break;
	case NI_M_Series_Next_SRC_Gate_Select:
		return NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		break;
	case NI_M_Series_Analog_Trigger_Out_Gate_Select:
		return NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT;
		break;
	case NI_M_Series_Logic_Low_Gate_Select:
		return NI_GPCT_LOGIC_LOW_GATE_SELECT;
		break;
	default:
		for (i = 0; i <= ni_m_series_max_rtsi_channel; ++i) {
			if (ni_m_series_gate_select ==
			    NI_M_Series_RTSI_Gate_Select(i)) {
				return NI_GPCT_RTSI_GATE_SELECT(i);
				break;
			}
		}
		if (i <= ni_m_series_max_rtsi_channel)
			break;
		for (i = 0; i <= ni_m_series_max_pfi_channel; ++i) {
			if (ni_m_series_gate_select ==
			    NI_M_Series_PFI_Gate_Select(i)) {
				return NI_GPCT_PFI_GATE_SELECT(i);
				break;
			}
		}
		if (i <= ni_m_series_max_pfi_channel)
			break;
		BUG();
		break;
	}
	return 0;
}