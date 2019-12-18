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
struct powerdomain {int state; int /*<<< orphan*/ * state_counter; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PWRDM_STATE_NOW 129 
#define  PWRDM_STATE_PREV 128 
 int /*<<< orphan*/  pm_dbg_update_time (struct powerdomain*,int) ; 
 int pwrdm_read_prev_pwrst (struct powerdomain*) ; 
 int pwrdm_read_pwrst (struct powerdomain*) ; 

__attribute__((used)) static int _pwrdm_state_switch(struct powerdomain *pwrdm, int flag)
{

	int prev;
	int state;

	if (pwrdm == NULL)
		return -EINVAL;

	state = pwrdm_read_pwrst(pwrdm);

	switch (flag) {
	case PWRDM_STATE_NOW:
		prev = pwrdm->state;
		break;
	case PWRDM_STATE_PREV:
		prev = pwrdm_read_prev_pwrst(pwrdm);
		if (pwrdm->state != prev)
			pwrdm->state_counter[prev]++;
		break;
	default:
		return -EINVAL;
	}

	if (state != prev)
		pwrdm->state_counter[state]++;

	pm_dbg_update_time(pwrdm, prev);

	pwrdm->state = state;

	return 0;
}