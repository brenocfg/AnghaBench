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
typedef  int u8 ;
struct cpufreq_freqs {scalar_t__ cpu; int /*<<< orphan*/  new; int /*<<< orphan*/  old; } ;
struct TYPE_2__ {int index; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int* cpuctl ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  sc520_freq_get_cpu_frequency (int /*<<< orphan*/ ) ; 
 TYPE_1__* sc520_freq_table ; 

__attribute__((used)) static void sc520_freq_set_cpu_state(unsigned int state)
{

	struct cpufreq_freqs	freqs;
	u8 clockspeed_reg;

	freqs.old = sc520_freq_get_cpu_frequency(0);
	freqs.new = sc520_freq_table[state].frequency;
	freqs.cpu = 0; /* AMD Elan is UP */

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	dprintk("attempting to set frequency to %i kHz\n",
			sc520_freq_table[state].frequency);

	local_irq_disable();

	clockspeed_reg = *cpuctl & ~0x03;
	*cpuctl = clockspeed_reg | sc520_freq_table[state].index;

	local_irq_enable();

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);
}