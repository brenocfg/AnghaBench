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
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dta_state; int /*<<< orphan*/ * dta_enabling; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 TYPE_1__ dtrace_anon ; 
 int /*<<< orphan*/  dtrace_enabling_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/ * dtrace_retained ; 

__attribute__((used)) static dtrace_state_t *
dtrace_anon_grab(void)
{
	dtrace_state_t *state;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	if ((state = dtrace_anon.dta_state) == NULL) {
		ASSERT(dtrace_anon.dta_enabling == NULL);
		return (NULL);
	}

	ASSERT(dtrace_anon.dta_enabling != NULL);
	ASSERT(dtrace_retained != NULL);

	dtrace_enabling_destroy(dtrace_anon.dta_enabling);
	dtrace_anon.dta_enabling = NULL;
	dtrace_anon.dta_state = NULL;

	return (state);
}