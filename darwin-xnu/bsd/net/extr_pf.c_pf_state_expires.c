#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_6__ {TYPE_1__* ptr; } ;
struct pf_state {size_t timeout; scalar_t__ expire; TYPE_2__ rule; } ;
struct TYPE_8__ {scalar_t__* timeout; } ;
struct TYPE_7__ {scalar_t__ states; } ;
struct TYPE_5__ {scalar_t__* timeout; scalar_t__ states; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 size_t PFTM_ADAPTIVE_END ; 
 size_t PFTM_ADAPTIVE_START ; 
 size_t PFTM_MAX ; 
 size_t PFTM_PURGE ; 
 size_t PFTM_UNLINKED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 TYPE_4__ pf_default_rule ; 
 int /*<<< orphan*/  pf_lock ; 
 TYPE_3__ pf_status ; 
 scalar_t__ pf_time_second () ; 

u_int64_t
pf_state_expires(const struct pf_state *state)
{
	u_int32_t	t;
	u_int32_t	start;
	u_int32_t	end;
	u_int32_t	states;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	/* handle all PFTM_* > PFTM_MAX here */
	if (state->timeout == PFTM_PURGE)
		return (pf_time_second());

	VERIFY(state->timeout != PFTM_UNLINKED);
	VERIFY(state->timeout < PFTM_MAX);
	t = state->rule.ptr->timeout[state->timeout];
	if (!t)
		t = pf_default_rule.timeout[state->timeout];
	start = state->rule.ptr->timeout[PFTM_ADAPTIVE_START];
	if (start) {
		end = state->rule.ptr->timeout[PFTM_ADAPTIVE_END];
		states = state->rule.ptr->states;
	} else {
		start = pf_default_rule.timeout[PFTM_ADAPTIVE_START];
		end = pf_default_rule.timeout[PFTM_ADAPTIVE_END];
		states = pf_status.states;
	}
	if (end && states > start && start < end) {
		if (states < end)
			return (state->expire + t * (end - states) /
			    (end - start));
		else
			return (pf_time_second());
	}
	return (state->expire + t);
}