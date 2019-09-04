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

__attribute__((used)) static int _ccv_nnc_gemm_back_bitmask(const int input_size, const int output_size, const uint64_t* const input_bitmasks, const int input_bitmask_size, const uint64_t* const output_bitmasks, const int output_bitmask_size)
{
	// Output the propagated error, gradient w.r.t. w and bias.
	if ((input_bitmasks[0] & 7u) == ((1u << 0) | (1u << 1) | (1u << 2) | (0 << 3)) && output_bitmasks[0] == ((1u << 0) | (1u << 1) | (1u << 2)))
		return 1;
	// No bias.
	if ((input_bitmasks[0] & 7u) == ((1u << 0) | (1u << 1) | (1u << 2) | (0 << 3)) && output_bitmasks[0] == ((1u << 0) | (1u << 1) | (0u << 2)))
		return 1;
	// Don't propagate error, only gradient w.r.t. w and bias.
	if ((input_bitmasks[0] & 7u) == ((1u << 0) | (1u << 1) | (0 << 2) | (0 << 3)) && output_bitmasks[0] == ((0 << 0) | (1u << 1) | (1u << 2)))
		return 1;
	// No bias.
	if ((input_bitmasks[0] & 7u) == ((1u << 0) | (1u << 1) | (0 << 2) | (0 << 3)) && output_bitmasks[0] == ((0 << 0) | (1u << 1) | (0u << 2)))
		return 1;
	return 0;
}