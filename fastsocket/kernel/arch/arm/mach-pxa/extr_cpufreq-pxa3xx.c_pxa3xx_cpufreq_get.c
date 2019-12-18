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
 unsigned int get_clk_frequency_khz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pxa3xx_cpufreq_get(unsigned int cpu)
{
	return get_clk_frequency_khz(0);
}