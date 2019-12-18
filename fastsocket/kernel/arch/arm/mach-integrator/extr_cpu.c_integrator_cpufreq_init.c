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
struct TYPE_2__ {int max_freq; int min_freq; int transition_latency; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  cur; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  integrator_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int integrator_cpufreq_init(struct cpufreq_policy *policy)
{

	/* set default policy and cpuinfo */
	policy->cpuinfo.max_freq = 160000;
	policy->cpuinfo.min_freq = 12000;
	policy->cpuinfo.transition_latency = 1000000; /* 1 ms, assumed */
	policy->cur = policy->min = policy->max = integrator_get(policy->cpu);

	return 0;
}