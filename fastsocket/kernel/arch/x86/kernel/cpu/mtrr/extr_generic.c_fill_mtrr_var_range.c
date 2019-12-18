#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct mtrr_var_range {void* mask_hi; void* mask_lo; void* base_hi; void* base_lo; } ;
struct TYPE_2__ {struct mtrr_var_range* var_ranges; } ;

/* Variables and functions */
 TYPE_1__ mtrr_state ; 

void fill_mtrr_var_range(unsigned int index,
		u32 base_lo, u32 base_hi, u32 mask_lo, u32 mask_hi)
{
	struct mtrr_var_range *vr;

	vr = mtrr_state.var_ranges;

	vr[index].base_lo = base_lo;
	vr[index].base_hi = base_hi;
	vr[index].mask_lo = mask_lo;
	vr[index].mask_hi = mask_hi;
}