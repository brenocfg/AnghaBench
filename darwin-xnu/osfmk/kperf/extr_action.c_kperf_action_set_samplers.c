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
typedef  int uint32_t ;
struct TYPE_2__ {int sample; } ;

/* Variables and functions */
 int EINVAL ; 
 int SAMPLER_PMC_CPU ; 
 int SAMPLER_PMC_THREAD ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 

int
kperf_action_set_samplers(unsigned actionid, uint32_t samplers)
{
	if ((actionid > actionc) || (actionid == 0)) {
		return EINVAL;
	}

	/* disallow both CPU and thread counters to be sampled in the same
	 * action */
	if ((samplers & SAMPLER_PMC_THREAD) && (samplers & SAMPLER_PMC_CPU)) {
		return EINVAL;
	}

	actionv[actionid - 1].sample = samplers;

	return 0;
}