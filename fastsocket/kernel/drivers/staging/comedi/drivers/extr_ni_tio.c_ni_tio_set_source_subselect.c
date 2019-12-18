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
struct ni_gpct_device {scalar_t__ variant; int /*<<< orphan*/ * regs; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Gi_Source_Subselect_Bit ; 
 unsigned int NITIO_Gi_Second_Gate_Reg (int /*<<< orphan*/ ) ; 
#define  NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS 131 
 unsigned int NI_GPCT_CLOCK_SRC_SELECT_MASK ; 
#define  NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS 130 
#define  NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS 129 
#define  NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS 128 
 scalar_t__ ni_gpct_variant_m_series ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int const) ; 

__attribute__((used)) static void ni_tio_set_source_subselect(struct ni_gpct *counter,
					unsigned int clock_source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const unsigned second_gate_reg =
	    NITIO_Gi_Second_Gate_Reg(counter->counter_index);

	if (counter_dev->variant != ni_gpct_variant_m_series)
		return;
	switch (clock_source & NI_GPCT_CLOCK_SRC_SELECT_MASK) {
		/* Gi_Source_Subselect is zero */
	case NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
	case NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		counter_dev->regs[second_gate_reg] &= ~Gi_Source_Subselect_Bit;
		break;
		/* Gi_Source_Subselect is one */
	case NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS:
	case NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS:
		counter_dev->regs[second_gate_reg] |= Gi_Source_Subselect_Bit;
		break;
		/* Gi_Source_Subselect doesn't matter */
	default:
		return;
		break;
	}
	write_register(counter, counter_dev->regs[second_gate_reg],
		       second_gate_reg);
}