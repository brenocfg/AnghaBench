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
struct cpufreq_frequency_table {int dummy; } ;

/* Variables and functions */
 struct cpufreq_frequency_table* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  show_table ; 

struct cpufreq_frequency_table *cpufreq_frequency_get_table(unsigned int cpu)
{
	return per_cpu(show_table, cpu);
}