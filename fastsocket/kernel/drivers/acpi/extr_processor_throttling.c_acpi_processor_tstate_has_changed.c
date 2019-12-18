#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tx; } ;
struct TYPE_5__ {int tx; } ;
struct acpi_processor_limit {TYPE_3__ user; TYPE_2__ thermal; } ;
struct TYPE_4__ {int state_count; int state; } ;
struct acpi_processor {int throttling_platform_limit; struct acpi_processor_limit limit; TYPE_1__ throttling; } ;

/* Variables and functions */
 int EINVAL ; 
 int acpi_processor_get_platform_limit (struct acpi_processor*) ; 
 int acpi_processor_set_throttling (struct acpi_processor*,int,int) ; 
 scalar_t__ ignore_tpc ; 

int acpi_processor_tstate_has_changed(struct acpi_processor *pr)
{
	int result = 0;
	int throttling_limit;
	int current_state;
	struct acpi_processor_limit *limit;
	int target_state;

	if (ignore_tpc)
		return 0;

	result = acpi_processor_get_platform_limit(pr);
	if (result) {
		/* Throttling Limit is unsupported */
		return result;
	}

	throttling_limit = pr->throttling_platform_limit;
	if (throttling_limit >= pr->throttling.state_count) {
		/* Uncorrect Throttling Limit */
		return -EINVAL;
	}

	current_state = pr->throttling.state;
	if (current_state > throttling_limit) {
		/*
		 * The current state can meet the requirement of
		 * _TPC limit. But it is reasonable that OSPM changes
		 * t-states from high to low for better performance.
		 * Of course the limit condition of thermal
		 * and user should be considered.
		 */
		limit = &pr->limit;
		target_state = throttling_limit;
		if (limit->thermal.tx > target_state)
			target_state = limit->thermal.tx;
		if (limit->user.tx > target_state)
			target_state = limit->user.tx;
	} else if (current_state == throttling_limit) {
		/*
		 * Unnecessary to change the throttling state
		 */
		return 0;
	} else {
		/*
		 * If the current state is lower than the limit of _TPC, it
		 * will be forced to switch to the throttling state defined
		 * by throttling_platfor_limit.
		 * Because the previous state meets with the limit condition
		 * of thermal and user, it is unnecessary to check it again.
		 */
		target_state = throttling_limit;
	}
	return acpi_processor_set_throttling(pr, target_state, false);
}