#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ mtrr_var_range_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_MTRR_PHYSBASE (int) ; 
 int /*<<< orphan*/  MSR_IA32_MTRR_PHYSMASK (int) ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtrr_set_var_ranges(const mtrr_var_range_t * range, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		wrmsr64(MSR_IA32_MTRR_PHYSBASE(i), range[i].base);
		wrmsr64(MSR_IA32_MTRR_PHYSMASK(i), range[i].mask);
	}
}