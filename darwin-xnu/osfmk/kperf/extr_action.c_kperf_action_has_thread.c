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
struct TYPE_2__ {int sample; } ;

/* Variables and functions */
 int SAMPLER_THREAD_MASK ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 

bool
kperf_action_has_thread(unsigned int actionid)
{
	if (actionid > actionc) {
		return false;
	}

	return (actionv[actionid - 1].sample & SAMPLER_THREAD_MASK);
}