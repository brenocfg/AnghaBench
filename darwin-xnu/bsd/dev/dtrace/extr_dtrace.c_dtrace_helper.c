#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_12__ {void** dtms_arg; } ;
typedef  TYPE_1__ dtrace_mstate_t ;
struct TYPE_13__ {int /*<<< orphan*/  dthps_vstate; TYPE_3__** dthps_actions; } ;
typedef  TYPE_2__ dtrace_helpers_t ;
struct TYPE_14__ {int dtha_nactions; int /*<<< orphan*/ ** dtha_actions; int /*<<< orphan*/ * dtha_predicate; struct TYPE_14__* dtha_next; } ;
typedef  TYPE_3__ dtrace_helper_action_t ;
typedef  int /*<<< orphan*/  dtrace_difo_t ;
struct TYPE_16__ {int cpuc_dtrace_flags; } ;
struct TYPE_15__ {TYPE_2__* p_dtrace_helpers; } ;
struct TYPE_11__ {size_t cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_10__* CPU ; 
 int CPU_DTRACE_FAULT ; 
 int DTRACE_HELPTRACE_DONE ; 
 int DTRACE_HELPTRACE_ERR ; 
 int DTRACE_HELPTRACE_NEXT ; 
 int DTRACE_NHELPER_ACTIONS ; 
 TYPE_9__* cpu_core ; 
 TYPE_8__* curproc ; 
 void* dtrace_dif_emulate (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_helper_trace (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int dtrace_helptrace_enabled ; 

__attribute__((used)) static uint64_t
dtrace_helper(int which, dtrace_mstate_t *mstate,
    dtrace_state_t *state, uint64_t arg0, uint64_t arg1)
{
	uint16_t *flags = &cpu_core[CPU->cpu_id].cpuc_dtrace_flags;
	uint64_t sarg0 = mstate->dtms_arg[0];
	uint64_t sarg1 = mstate->dtms_arg[1];
	uint64_t rval = 0;
	dtrace_helpers_t *helpers = curproc->p_dtrace_helpers;
	dtrace_helper_action_t *helper;
	dtrace_vstate_t *vstate;
	dtrace_difo_t *pred;
	int i, trace = dtrace_helptrace_enabled;

	ASSERT(which >= 0 && which < DTRACE_NHELPER_ACTIONS);

	if (helpers == NULL)
		return (0);

	if ((helper = helpers->dthps_actions[which]) == NULL)
		return (0);

	vstate = &helpers->dthps_vstate;
	mstate->dtms_arg[0] = arg0;
	mstate->dtms_arg[1] = arg1;

	/*
	 * Now iterate over each helper.  If its predicate evaluates to 'true',
	 * we'll call the corresponding actions.  Note that the below calls
	 * to dtrace_dif_emulate() may set faults in machine state.  This is
	 * okay:  our caller (the outer dtrace_dif_emulate()) will simply plow
	 * the stored DIF offset with its own (which is the desired behavior).
	 * Also, note the calls to dtrace_dif_emulate() may allocate scratch
	 * from machine state; this is okay, too.
	 */
	for (; helper != NULL; helper = helper->dtha_next) {
		if ((pred = helper->dtha_predicate) != NULL) {
			if (trace)
				dtrace_helper_trace(helper, mstate, vstate, 0);

			if (!dtrace_dif_emulate(pred, mstate, vstate, state))
				goto next;

			if (*flags & CPU_DTRACE_FAULT)
				goto err;
		}

		for (i = 0; i < helper->dtha_nactions; i++) {
			if (trace)
				dtrace_helper_trace(helper,
				    mstate, vstate, i + 1);

			rval = dtrace_dif_emulate(helper->dtha_actions[i],
			    mstate, vstate, state);

			if (*flags & CPU_DTRACE_FAULT)
				goto err;
		}

next:
		if (trace)
			dtrace_helper_trace(helper, mstate, vstate,
			    DTRACE_HELPTRACE_NEXT);
	}

	if (trace)
		dtrace_helper_trace(helper, mstate, vstate,
		    DTRACE_HELPTRACE_DONE);

	/*
	 * Restore the arg0 that we saved upon entry.
	 */
	mstate->dtms_arg[0] = sarg0;
	mstate->dtms_arg[1] = sarg1;

	return (rval);

err:
	if (trace)
		dtrace_helper_trace(helper, mstate, vstate,
		    DTRACE_HELPTRACE_ERR);

	/*
	 * Restore the arg0 that we saved upon entry.
	 */
	mstate->dtms_arg[0] = sarg0;
	mstate->dtms_arg[1] = sarg1;

	return (0);
}