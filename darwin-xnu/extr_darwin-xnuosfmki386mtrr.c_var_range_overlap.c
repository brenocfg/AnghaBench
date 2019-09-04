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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int base; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ mtrr_var_range_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int IA32_MTRR_PHYSBASE_MASK ; 
 int IA32_MTRR_PHYSBASE_TYPE ; 
 int MASK_TO_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ MTRR_TYPE_UNCACHEABLE ; 
 scalar_t__ MTRR_TYPE_WRITEBACK ; 

__attribute__((used)) static int
var_range_overlap(mtrr_var_range_t * range, addr64_t address,
		  uint64_t length, uint32_t type)
{
	uint64_t  v_address, v_length;
	uint32_t  v_type;
	int       result = 0;  /* no overlap, or overlap ok */

	v_address = range->base & IA32_MTRR_PHYSBASE_MASK;
	v_type    = (uint32_t)(range->base & IA32_MTRR_PHYSBASE_TYPE);
	v_length  = MASK_TO_LEN(range->mask);

	/* detect range overlap */
	if ((v_address >= address && v_address < (address + length)) ||
	    (address >= v_address && address < (v_address + v_length))) {

		if (v_address == address && v_length == length && v_type == type)
			result = 1; /* identical overlap ok */
		else if ( v_type == MTRR_TYPE_UNCACHEABLE &&
			    type == MTRR_TYPE_UNCACHEABLE ) {
			/* UC ranges can overlap */
		}
		else if ((v_type == MTRR_TYPE_UNCACHEABLE &&
		            type == MTRR_TYPE_WRITEBACK)  ||
			 (v_type == MTRR_TYPE_WRITEBACK &&
			    type == MTRR_TYPE_UNCACHEABLE)) {
			/* UC/WB can overlap - effective type becomes UC */
		}
		else {
			/* anything else may cause undefined behavior */
			result = -1;
		}
	}

	return result;
}