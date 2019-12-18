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

__attribute__((used)) static int _ccv_nnc_batch_norm_enforce_inplace(const int input_idx, const int input_size, const int output_idx, const int output_size)
{
	if (input_idx == 3 && output_idx == 1)
		return 1;
	if (input_idx == 4 && output_idx == 2)
		return 1;
	return 0;
}