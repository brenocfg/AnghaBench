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
 unsigned int CR_CHAN (unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  Gi_Gate_Select_Bits (unsigned int) ; 
 int /*<<< orphan*/  Gi_Gate_Select_Mask ; 
 int /*<<< orphan*/  NITIO_Gi_Input_Select_Reg (int /*<<< orphan*/ ) ; 
#define  NI_GPCT_AI_START1_GATE_SELECT 135 
#define  NI_GPCT_AI_START2_GATE_SELECT 134 
#define  NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT 133 
#define  NI_GPCT_LOGIC_LOW_GATE_SELECT 132 
#define  NI_GPCT_NEXT_OUT_GATE_SELECT 131 
#define  NI_GPCT_NEXT_SOURCE_GATE_SELECT 130 
 unsigned int const NI_GPCT_PFI_GATE_SELECT (unsigned int) ; 
#define  NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT 129 
 unsigned int const NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
#define  NI_GPCT_TIMESTAMP_MUX_GATE_SELECT 128 
 unsigned int ni_m_series_max_pfi_channel ; 
 unsigned int ni_m_series_max_rtsi_channel ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_m_series_set_first_gate(struct ni_gpct *counter,
				      unsigned int gate_source)
{
	const unsigned selected_gate = CR_CHAN(gate_source);
	/* bits of selected_gate that may be meaningful to input select register */
	const unsigned selected_gate_mask = 0x1f;
	unsigned ni_m_series_gate_select;
	unsigned i;

	switch (selected_gate) {
	case NI_GPCT_TIMESTAMP_MUX_GATE_SELECT:
	case NI_GPCT_AI_START2_GATE_SELECT:
	case NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT:
	case NI_GPCT_NEXT_OUT_GATE_SELECT:
	case NI_GPCT_AI_START1_GATE_SELECT:
	case NI_GPCT_NEXT_SOURCE_GATE_SELECT:
	case NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT:
	case NI_GPCT_LOGIC_LOW_GATE_SELECT:
		ni_m_series_gate_select = selected_gate & selected_gate_mask;
		break;
	default:
		for (i = 0; i <= ni_m_series_max_rtsi_channel; ++i) {
			if (selected_gate == NI_GPCT_RTSI_GATE_SELECT(i)) {
				ni_m_series_gate_select =
				    selected_gate & selected_gate_mask;
				break;
			}
		}
		if (i <= ni_m_series_max_rtsi_channel)
			break;
		for (i = 0; i <= ni_m_series_max_pfi_channel; ++i) {
			if (selected_gate == NI_GPCT_PFI_GATE_SELECT(i)) {
				ni_m_series_gate_select =
				    selected_gate & selected_gate_mask;
				break;
			}
		}
		if (i <= ni_m_series_max_pfi_channel)
			break;
		return -EINVAL;
		break;
	}
	ni_tio_set_bits(counter,
			NITIO_Gi_Input_Select_Reg(counter->counter_index),
			Gi_Gate_Select_Mask,
			Gi_Gate_Select_Bits(ni_m_series_gate_select));
	return 0;
}