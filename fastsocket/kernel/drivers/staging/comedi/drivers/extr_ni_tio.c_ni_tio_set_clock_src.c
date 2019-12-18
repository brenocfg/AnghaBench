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
typedef  unsigned int uint64_t ;
struct ni_gpct_device {int variant; } ;
struct ni_gpct {unsigned int clock_period_ps; int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 unsigned int Gi_Prescale_X2_Bit (int) ; 
 unsigned int Gi_Prescale_X8_Bit (int) ; 
 unsigned int Gi_Source_Polarity_Bit ; 
 unsigned int Gi_Source_Select_Mask ; 
 int /*<<< orphan*/  NITIO_Gi_Counting_Mode_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Input_Select_Reg (int /*<<< orphan*/ ) ; 
 unsigned int NI_GPCT_INVERT_CLOCK_SRC_BIT ; 
#define  NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS 133 
 unsigned int NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK ; 
#define  NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS 132 
#define  NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS 131 
 unsigned int ni_660x_source_select_bits (unsigned int) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 unsigned int ni_m_series_source_select_bits (unsigned int) ; 
 scalar_t__ ni_tio_counting_mode_registers_present (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_source_subselect (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_sync_mode (struct ni_gpct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_tio_set_clock_src(struct ni_gpct *counter,
				unsigned int clock_source,
				unsigned int period_ns)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned input_select_bits = 0;
	static const uint64_t pico_per_nano = 1000;

/*FIXME: validate clock source */
	switch (counter_dev->variant) {
	case ni_gpct_variant_660x:
		input_select_bits |= ni_660x_source_select_bits(clock_source);
		break;
	case ni_gpct_variant_e_series:
	case ni_gpct_variant_m_series:
		input_select_bits |=
		    ni_m_series_source_select_bits(clock_source);
		break;
	default:
		BUG();
		break;
	}
	if (clock_source & NI_GPCT_INVERT_CLOCK_SRC_BIT)
		input_select_bits |= Gi_Source_Polarity_Bit;
	ni_tio_set_bits(counter,
			NITIO_Gi_Input_Select_Reg(counter->counter_index),
			Gi_Source_Select_Mask | Gi_Source_Polarity_Bit,
			input_select_bits);
	ni_tio_set_source_subselect(counter, clock_source);
	if (ni_tio_counting_mode_registers_present(counter_dev)) {
		const unsigned prescaling_mode =
		    clock_source & NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK;
		unsigned counting_mode_bits = 0;

		switch (prescaling_mode) {
		case NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS:
			break;
		case NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS:
			counting_mode_bits |=
			    Gi_Prescale_X2_Bit(counter_dev->variant);
			break;
		case NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS:
			counting_mode_bits |=
			    Gi_Prescale_X8_Bit(counter_dev->variant);
			break;
		default:
			return -EINVAL;
			break;
		}
		ni_tio_set_bits(counter,
				NITIO_Gi_Counting_Mode_Reg(counter->
							   counter_index),
				Gi_Prescale_X2_Bit(counter_dev->variant) |
				Gi_Prescale_X8_Bit(counter_dev->variant),
				counting_mode_bits);
	}
	counter->clock_period_ps = pico_per_nano * period_ns;
	ni_tio_set_sync_mode(counter, 0);
	return 0;
}