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
 int /*<<< orphan*/  clk_arm ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int s3c_cpufreq_get(unsigned int cpu)
{
	return clk_get_rate(clk_arm) / 1000;
}