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

__attribute__((used)) static int _ccv_nnc_softmax_crossentropy_allow_inplace_back(const int input_idx, const int input_size, const int output_idx, const int output_size)
{
	if (input_idx == 1 && output_idx == 0)
		return 1;
	if (input_idx == 2 && output_idx == 0)
		return 1;
	else if (input_idx == 5 && output_idx == 0)
		return 1;
	return 0;
}