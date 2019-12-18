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
 long long cpu_clock (int) ; 

__attribute__((used)) static unsigned long get_timestamp(int this_cpu)
{
	return cpu_clock(this_cpu) >> 30LL;  /* 2^30 ~= 10^9 */
}