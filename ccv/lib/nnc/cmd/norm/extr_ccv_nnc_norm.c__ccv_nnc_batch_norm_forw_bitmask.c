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

/* Variables and functions */

__attribute__((used)) static int _ccv_nnc_batch_norm_forw_bitmask(const int input_size, const int output_size, const uint64_t* const input_bitmasks, const int input_bitmask_size, const uint64_t* const output_bitmasks, const int output_bitmask_size)
{
	// 5 inputs (x, scale, bias, mean, var)
	// 1 outputs (y)
	if (input_bitmasks[0] == 31u && output_bitmasks[0] == 1u)
		return 1;
	// 5 inputs (x, scale, bias, mean, var)
	// 5 outputs (y, mean, var, saved_mean, saved_inv_var)
	// Both mean and var in output is inplace for the input mean, var
	if (input_bitmasks[0] == 31u && output_bitmasks[0] == 31u)
		return 1;
	return 0;
}