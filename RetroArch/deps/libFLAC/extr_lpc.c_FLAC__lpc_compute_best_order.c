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
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 double FLAC__lpc_compute_expected_bits_per_residual_sample_with_error_scale (double const,double) ; 

unsigned FLAC__lpc_compute_best_order(const double lpc_error[], unsigned max_order, unsigned total_samples, unsigned overhead_bits_per_order)
{
	unsigned order, indx, best_index; /* 'index' the index into lpc_error; index==order-1 since lpc_error[0] is for order==1, lpc_error[1] is for order==2, etc */
	double bits, best_bits, error_scale;

	FLAC__ASSERT(max_order > 0);
	FLAC__ASSERT(total_samples > 0);

	error_scale = 0.5 / (double)total_samples;

	best_index = 0;
	best_bits = (unsigned)(-1);

	for(indx = 0, order = 1; indx < max_order; indx++, order++) {
		bits = FLAC__lpc_compute_expected_bits_per_residual_sample_with_error_scale(lpc_error[indx], error_scale) * (double)(total_samples - order) + (double)(order * overhead_bits_per_order);
		if(bits < best_bits) {
			best_index = indx;
			best_bits = bits;
		}
	}

	return best_index+1; /* +1 since indx of lpc_error[] is order-1 */
}