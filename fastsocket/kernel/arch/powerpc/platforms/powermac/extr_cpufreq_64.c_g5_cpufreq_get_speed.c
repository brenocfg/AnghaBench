#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int frequency; } ;

/* Variables and functions */
 TYPE_1__* g5_cpu_freqs ; 
 size_t g5_pmode_cur ; 

__attribute__((used)) static unsigned int g5_cpufreq_get_speed(unsigned int cpu)
{
	return g5_cpu_freqs[g5_pmode_cur].frequency;
}