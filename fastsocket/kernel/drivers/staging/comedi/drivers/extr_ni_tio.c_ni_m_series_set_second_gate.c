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
 int /*<<< orphan*/  Gi_Second_Gate_Mode_Bit ; 
 int /*<<< orphan*/  Gi_Second_Gate_Select_Bits (unsigned int) ; 
 int /*<<< orphan*/  Gi_Second_Gate_Select_Mask ; 
 unsigned int NITIO_Gi_Second_Gate_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int const) ; 

__attribute__((used)) static int ni_m_series_set_second_gate(struct ni_gpct *counter,
				       unsigned int gate_source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const unsigned second_gate_reg =
	    NITIO_Gi_Second_Gate_Reg(counter->counter_index);
	const unsigned selected_second_gate = CR_CHAN(gate_source);
	/* bits of second_gate that may be meaningful to second gate register */
	static const unsigned selected_second_gate_mask = 0x1f;
	unsigned ni_m_series_second_gate_select;

	/* FIXME: We don't know what the m-series second gate codes are, so we'll just pass
	   the bits through for now. */
	switch (selected_second_gate) {
	default:
		ni_m_series_second_gate_select =
		    selected_second_gate & selected_second_gate_mask;
		break;
	};
	counter_dev->regs[second_gate_reg] |= Gi_Second_Gate_Mode_Bit;
	counter_dev->regs[second_gate_reg] &= ~Gi_Second_Gate_Select_Mask;
	counter_dev->regs[second_gate_reg] |=
	    Gi_Second_Gate_Select_Bits(ni_m_series_second_gate_select);
	write_register(counter, counter_dev->regs[second_gate_reg],
		       second_gate_reg);
	return 0;
}