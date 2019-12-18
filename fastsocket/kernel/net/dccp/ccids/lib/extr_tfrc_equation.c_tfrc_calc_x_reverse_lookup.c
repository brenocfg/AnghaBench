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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_WARN (char*,scalar_t__) ; 
 int TFRC_CALC_X_ARRSIZE ; 
 int TFRC_CALC_X_SPLIT ; 
 scalar_t__ TFRC_SMALLEST_P ; 
 int tfrc_binsearch (scalar_t__,int) ; 
 scalar_t__** tfrc_calc_x_lookup ; 

u32 tfrc_calc_x_reverse_lookup(u32 fvalue)
{
	int index;

	if (fvalue == 0)	/* f(p) = 0  whenever  p = 0 */
		return 0;

	/* Error cases. */
	if (fvalue < tfrc_calc_x_lookup[0][1]) {
		DCCP_WARN("fvalue %u smaller than resolution\n", fvalue);
		return TFRC_SMALLEST_P;
	}
	if (fvalue > tfrc_calc_x_lookup[TFRC_CALC_X_ARRSIZE - 1][0]) {
		DCCP_WARN("fvalue %u exceeds bounds!\n", fvalue);
		return 1000000;
	}

	if (fvalue <= tfrc_calc_x_lookup[TFRC_CALC_X_ARRSIZE - 1][1]) {
		index = tfrc_binsearch(fvalue, 1);
		return (index + 1) * TFRC_CALC_X_SPLIT / TFRC_CALC_X_ARRSIZE;
	}

	/* else ... it must be in the coarse-grained column */
	index = tfrc_binsearch(fvalue, 0);
	return (index + 1) * 1000000 / TFRC_CALC_X_ARRSIZE;
}