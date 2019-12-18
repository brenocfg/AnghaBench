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
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 
 unsigned long ppc_tb_freq ; 

__attribute__((used)) static unsigned long long period_to_sec(unsigned int period)
{
	unsigned long long tmp = 1ULL << (64 - period);
	unsigned long tmp2 = ppc_tb_freq;

	/* tmp may be a very large number and we don't want to overflow,
	 * so divide the timebase freq instead of multiplying tmp
	 */
	tmp2 = tmp2 / 5 * 2;

	do_div(tmp, tmp2);
	return tmp;
}