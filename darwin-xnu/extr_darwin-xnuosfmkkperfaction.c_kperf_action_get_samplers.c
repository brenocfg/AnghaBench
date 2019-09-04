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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ sample; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 

int
kperf_action_get_samplers(unsigned actionid, uint32_t *samplers_out)
{
	if ((actionid > actionc)) {
		return EINVAL;
	}

	if (actionid == 0) {
		*samplers_out = 0; /* "NULL" action */
	} else {
		*samplers_out = actionv[actionid - 1].sample;
	}

	return 0;
}