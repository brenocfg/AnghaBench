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
typedef  int /*<<< orphan*/  turnstile_stats_update_flags_t ;
struct turnstile {scalar_t__ ts_priority; } ;
struct TYPE_2__ {scalar_t__* qos_pri; } ;

/* Variables and functions */
 size_t THREAD_QOS_USER_INTERACTIVE ; 
 int /*<<< orphan*/  TSU_ABOVE_UI_PRI_CHANGE ; 
 int /*<<< orphan*/  TSU_FLAGS_NONE ; 
 scalar_t__ TURNSTILE_ULOCK ; 
 TYPE_1__ thread_qos_policy_params ; 
 scalar_t__ turnstile_get_type (struct turnstile*) ; 

__attribute__((used)) static turnstile_stats_update_flags_t
turnstile_get_update_flags_for_above_UI_pri_change(struct turnstile *turnstile)
{
	if (turnstile->ts_priority >
	    (thread_qos_policy_params.qos_pri[THREAD_QOS_USER_INTERACTIVE] + 1) &&
	    turnstile_get_type(turnstile) != TURNSTILE_ULOCK) {
		return TSU_ABOVE_UI_PRI_CHANGE;

	}

	return TSU_FLAGS_NONE;
}