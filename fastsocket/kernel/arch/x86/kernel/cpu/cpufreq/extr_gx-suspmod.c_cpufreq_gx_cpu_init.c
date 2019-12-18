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
struct TYPE_2__ {unsigned int min_freq; unsigned int max_freq; int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {scalar_t__ cpu; unsigned int min; unsigned int max; unsigned int cur; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_ETERNAL ; 
 int /*<<< orphan*/  CX86_DIR1 ; 
 int ENODEV ; 
 unsigned int POLICY_MIN_DIV ; 
 int cpu_khz ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int* gx_freq_mult ; 
 unsigned int gx_get_cpuspeed (int /*<<< orphan*/ ) ; 
 unsigned int max_duration ; 
 int pci_busclk ; 
 unsigned int stock_freq ; 

__attribute__((used)) static int cpufreq_gx_cpu_init(struct cpufreq_policy *policy)
{
	unsigned int maxfreq, curfreq;

	if (!policy || policy->cpu != 0)
		return -ENODEV;

	/* determine maximum frequency */
	if (pci_busclk)
		maxfreq = pci_busclk * gx_freq_mult[getCx86(CX86_DIR1) & 0x0f];
	else if (cpu_khz)
		maxfreq = cpu_khz;
	else
		maxfreq = 30000 * gx_freq_mult[getCx86(CX86_DIR1) & 0x0f];

	stock_freq = maxfreq;
	curfreq = gx_get_cpuspeed(0);

	dprintk("cpu max frequency is %d.\n", maxfreq);
	dprintk("cpu current frequency is %dkHz.\n", curfreq);

	/* setup basic struct for cpufreq API */
	policy->cpu = 0;

	if (max_duration < POLICY_MIN_DIV)
		policy->min = maxfreq / max_duration;
	else
		policy->min = maxfreq / POLICY_MIN_DIV;
	policy->max = maxfreq;
	policy->cur = curfreq;
	policy->cpuinfo.min_freq = maxfreq / max_duration;
	policy->cpuinfo.max_freq = maxfreq;
	policy->cpuinfo.transition_latency = CPUFREQ_ETERNAL;

	return 0;
}