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
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct clockdomain {TYPE_1__ pwrdm; } ;

/* Variables and functions */
 int EINVAL ; 
 int pwrdm_state_switch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwrdm_wait_transition (int /*<<< orphan*/ *) ; 

int pwrdm_clkdm_state_switch(struct clockdomain *clkdm)
{
	if (clkdm != NULL && clkdm->pwrdm.ptr != NULL) {
		pwrdm_wait_transition(clkdm->pwrdm.ptr);
		return pwrdm_state_switch(clkdm->pwrdm.ptr);
	}

	return -EINVAL;
}