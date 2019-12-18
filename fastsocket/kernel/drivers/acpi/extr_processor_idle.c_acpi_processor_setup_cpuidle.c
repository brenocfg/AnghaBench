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
struct cpuidle_state {char* name; char* desc; int exit_latency; int target_residency; void* enter; scalar_t__ flags; int /*<<< orphan*/  power_usage; } ;
struct cpuidle_device {int state_count; struct cpuidle_state* safe_state; struct cpuidle_state* states; int /*<<< orphan*/  cpu; } ;
struct acpi_processor_cx {int type; int latency; int /*<<< orphan*/  entry_method; int /*<<< orphan*/  power; int /*<<< orphan*/  desc; int /*<<< orphan*/  valid; } ;
struct TYPE_5__ {scalar_t__ power; int /*<<< orphan*/  bm_check; int /*<<< orphan*/  has_cst; int /*<<< orphan*/  power_setup_done; } ;
struct TYPE_4__ {struct acpi_processor_cx* states; struct cpuidle_device dev; } ;
struct acpi_processor {TYPE_2__ flags; TYPE_1__ power; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CSTATE_FFH ; 
 int ACPI_FADT_C2_MP_SUPPORTED ; 
 int ACPI_PROCESSOR_MAX_POWER ; 
#define  ACPI_STATE_C1 130 
#define  ACPI_STATE_C2 129 
#define  ACPI_STATE_C3 128 
 int /*<<< orphan*/  CPUIDLE_DESC_LEN ; 
 int CPUIDLE_DRIVER_STATE_START ; 
 scalar_t__ CPUIDLE_FLAG_BALANCED ; 
 scalar_t__ CPUIDLE_FLAG_CHECK_BM ; 
 scalar_t__ CPUIDLE_FLAG_DEEP ; 
 scalar_t__ CPUIDLE_FLAG_SHALLOW ; 
 scalar_t__ CPUIDLE_FLAG_TIME_VALID ; 
 int /*<<< orphan*/  CPUIDLE_NAME_LEN ; 
 int CPUIDLE_STATE_MAX ; 
 int EINVAL ; 
 TYPE_3__ acpi_gbl_FADT ; 
 void* acpi_idle_enter_bm ; 
 void* acpi_idle_enter_c1 ; 
 void* acpi_idle_enter_simple ; 
 int /*<<< orphan*/  cpuidle_set_statedata (struct cpuidle_state*,struct acpi_processor_cx*) ; 
 int latency_factor ; 
 int max_cstate ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_processor_setup_cpuidle(struct acpi_processor *pr)
{
	int i, count = CPUIDLE_DRIVER_STATE_START;
	struct acpi_processor_cx *cx;
	struct cpuidle_state *state;
	struct cpuidle_device *dev = &pr->power.dev;

	if (!pr->flags.power_setup_done)
		return -EINVAL;

	if (pr->flags.power == 0) {
		return -EINVAL;
	}

	dev->cpu = pr->id;
	for (i = 0; i < CPUIDLE_STATE_MAX; i++) {
		dev->states[i].name[0] = '\0';
		dev->states[i].desc[0] = '\0';
	}

	if (max_cstate == 0)
		max_cstate = 1;

	for (i = 1; i < ACPI_PROCESSOR_MAX_POWER && i <= max_cstate; i++) {
		cx = &pr->power.states[i];
		state = &dev->states[count];

		if (!cx->valid)
			continue;

#ifdef CONFIG_HOTPLUG_CPU
		if ((cx->type != ACPI_STATE_C1) && (num_online_cpus() > 1) &&
		    !pr->flags.has_cst &&
		    !(acpi_gbl_FADT.flags & ACPI_FADT_C2_MP_SUPPORTED))
			continue;
#endif
		cpuidle_set_statedata(state, cx);

		snprintf(state->name, CPUIDLE_NAME_LEN, "C%d", i);
		strncpy(state->desc, cx->desc, CPUIDLE_DESC_LEN);
		state->exit_latency = cx->latency;
		state->target_residency = cx->latency * latency_factor;
		state->power_usage = cx->power;

		state->flags = 0;
		switch (cx->type) {
			case ACPI_STATE_C1:
			state->flags |= CPUIDLE_FLAG_SHALLOW;
			if (cx->entry_method == ACPI_CSTATE_FFH)
				state->flags |= CPUIDLE_FLAG_TIME_VALID;

			state->enter = acpi_idle_enter_c1;
			dev->safe_state = state;
			break;

			case ACPI_STATE_C2:
			state->flags |= CPUIDLE_FLAG_BALANCED;
			state->flags |= CPUIDLE_FLAG_TIME_VALID;
			state->enter = acpi_idle_enter_simple;
			dev->safe_state = state;
			break;

			case ACPI_STATE_C3:
			state->flags |= CPUIDLE_FLAG_DEEP;
			state->flags |= CPUIDLE_FLAG_TIME_VALID;
			state->flags |= CPUIDLE_FLAG_CHECK_BM;
			state->enter = pr->flags.bm_check ?
					acpi_idle_enter_bm :
					acpi_idle_enter_simple;
			break;
		}

		count++;
		if (count == CPUIDLE_STATE_MAX)
			break;
	}

	dev->state_count = count;

	if (!count)
		return -EINVAL;

	return 0;
}