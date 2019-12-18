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
 int CCV_NNC_MAX_DIM_ALLOC ; 

__attribute__((used)) static inline size_t ccv_nnc_dimension_count(const int dim[CCV_NNC_MAX_DIM_ALLOC])
{
	if (dim[0] == 0)
		return 0;
	int i;
	size_t count = 1;
	for (i = 0; i < CCV_NNC_MAX_DIM_ALLOC && dim[i] > 0; i++)
		count *= dim[i];
	return count;
}