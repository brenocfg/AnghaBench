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
 unsigned int CR_EDGE ; 
 unsigned int CR_INVERT ; 
 unsigned int Gi_Gate_Polarity_Bit ; 
 unsigned int Gi_Gating_Mode_Mask ; 
 unsigned int Gi_Level_Gating_Bits ; 
 unsigned int Gi_Rising_Edge_Gating_Bits ; 
 int /*<<< orphan*/  NITIO_Gi_Mode_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int const,unsigned int) ; 

__attribute__((used)) static void ni_tio_set_first_gate_modifiers(struct ni_gpct *counter,
					    unsigned int gate_source)
{
	const unsigned mode_mask = Gi_Gate_Polarity_Bit | Gi_Gating_Mode_Mask;
	unsigned mode_values = 0;

	if (gate_source & CR_INVERT) {
		mode_values |= Gi_Gate_Polarity_Bit;
	}
	if (gate_source & CR_EDGE) {
		mode_values |= Gi_Rising_Edge_Gating_Bits;
	} else {
		mode_values |= Gi_Level_Gating_Bits;
	}
	ni_tio_set_bits(counter, NITIO_Gi_Mode_Reg(counter->counter_index),
			mode_mask, mode_values);
}