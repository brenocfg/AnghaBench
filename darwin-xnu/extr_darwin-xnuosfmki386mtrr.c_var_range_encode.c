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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int base; int mask; } ;
typedef  TYPE_1__ mtrr_var_range_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int IA32_MTRR_PHYMASK_VALID ; 
 int IA32_MTRR_PHYSBASE_MASK ; 
 scalar_t__ IA32_MTRR_PHYSBASE_TYPE ; 
 int LEN_TO_MASK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
var_range_encode(mtrr_var_range_t * range, addr64_t address,
		 uint64_t length, uint32_t type, int valid)
{
	range->base = (address & IA32_MTRR_PHYSBASE_MASK) |
		      (type    & (uint32_t)IA32_MTRR_PHYSBASE_TYPE);

	range->mask = LEN_TO_MASK(length) |
		      (valid ? IA32_MTRR_PHYMASK_VALID : 0);
}