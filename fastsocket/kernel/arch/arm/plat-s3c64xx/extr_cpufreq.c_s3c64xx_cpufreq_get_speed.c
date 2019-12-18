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
 int /*<<< orphan*/  armclk ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int s3c64xx_cpufreq_get_speed(unsigned int cpu)
{
	if (cpu != 0)
		return 0;

	return clk_get_rate(armclk) / 1000;
}