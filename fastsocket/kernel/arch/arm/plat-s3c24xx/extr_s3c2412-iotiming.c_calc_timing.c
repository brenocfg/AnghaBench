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
 unsigned int EINVAL ; 
 unsigned int to_div (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int calc_timing(unsigned int hwtm, unsigned int clk_tns,
				unsigned int *err)
{
	unsigned int ret = to_div(hwtm, clk_tns);

	if (ret > 0xf)
		*err = -EINVAL;

	return ret;
}