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
typedef  scalar_t__ uint64_t ;
struct ni_gpct_device {int /*<<< orphan*/  variant; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int Gi_Alternate_Sync_Bit (int /*<<< orphan*/ ) ; 
 int Gi_Counting_Mode_Mask ; 
#define  Gi_Counting_Mode_QuadratureX1_Bits 131 
#define  Gi_Counting_Mode_QuadratureX2_Bits 130 
#define  Gi_Counting_Mode_QuadratureX4_Bits 129 
#define  Gi_Counting_Mode_Sync_Source_Bits 128 
 unsigned int NITIO_Gi_Counting_Mode_Reg (int /*<<< orphan*/ ) ; 
 scalar_t__ ni_tio_clock_period_ps (struct ni_gpct*,int /*<<< orphan*/ ) ; 
 scalar_t__ ni_tio_counting_mode_registers_present (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_generic_clock_src_select (struct ni_gpct*) ; 
 int ni_tio_get_soft_copy (struct ni_gpct*,unsigned int const) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,unsigned int const,int,int) ; 

__attribute__((used)) static void ni_tio_set_sync_mode(struct ni_gpct *counter, int force_alt_sync)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const unsigned counting_mode_reg =
	    NITIO_Gi_Counting_Mode_Reg(counter->counter_index);
	static const uint64_t min_normal_sync_period_ps = 25000;
	const uint64_t clock_period_ps = ni_tio_clock_period_ps(counter,
								ni_tio_generic_clock_src_select
								(counter));

	if (ni_tio_counting_mode_registers_present(counter_dev) == 0)
		return;

	switch (ni_tio_get_soft_copy(counter,
				     counting_mode_reg) & Gi_Counting_Mode_Mask)
	{
	case Gi_Counting_Mode_QuadratureX1_Bits:
	case Gi_Counting_Mode_QuadratureX2_Bits:
	case Gi_Counting_Mode_QuadratureX4_Bits:
	case Gi_Counting_Mode_Sync_Source_Bits:
		force_alt_sync = 1;
		break;
	default:
		break;
	}
	/* It's not clear what we should do if clock_period is unknown, so we are not
	   using the alt sync bit in that case, but allow the caller to decide by using the
	   force_alt_sync parameter. */
	if (force_alt_sync ||
	    (clock_period_ps && clock_period_ps < min_normal_sync_period_ps)) {
		ni_tio_set_bits(counter, counting_mode_reg,
				Gi_Alternate_Sync_Bit(counter_dev->variant),
				Gi_Alternate_Sync_Bit(counter_dev->variant));
	} else {
		ni_tio_set_bits(counter, counting_mode_reg,
				Gi_Alternate_Sync_Bit(counter_dev->variant),
				0x0);
	}
}