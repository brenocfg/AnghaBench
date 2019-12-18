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
typedef  int /*<<< orphan*/  pxa_freqs_t ;

/* Variables and functions */
 scalar_t__ cpu_is_pxa25x () ; 
 scalar_t__ cpu_is_pxa27x () ; 
 struct cpufreq_frequency_table* pxa255_run_freq_table ; 
 int /*<<< orphan*/ * pxa255_run_freqs ; 
 struct cpufreq_frequency_table* pxa255_turbo_freq_table ; 
 int /*<<< orphan*/ * pxa255_turbo_freqs ; 
 int /*<<< orphan*/  pxa255_turbo_table ; 
 struct cpufreq_frequency_table* pxa27x_freq_table ; 
 int /*<<< orphan*/ * pxa27x_freqs ; 

__attribute__((used)) static void find_freq_tables(struct cpufreq_frequency_table **freq_table,
			     pxa_freqs_t **pxa_freqs)
{
	if (cpu_is_pxa25x()) {
		if (!pxa255_turbo_table) {
			*pxa_freqs = pxa255_run_freqs;
			*freq_table = pxa255_run_freq_table;
		} else {
			*pxa_freqs = pxa255_turbo_freqs;
			*freq_table = pxa255_turbo_freq_table;
		}
	}
	if (cpu_is_pxa27x()) {
		*pxa_freqs = pxa27x_freqs;
		*freq_table = pxa27x_freq_table;
	}
}