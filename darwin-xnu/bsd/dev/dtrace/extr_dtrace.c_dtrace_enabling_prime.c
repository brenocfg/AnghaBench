#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_6__ {int dten_primed; int dten_ndesc; int /*<<< orphan*/ * dten_desc; int /*<<< orphan*/  dten_current; TYPE_1__* dten_vstate; struct TYPE_6__* dten_next; } ;
typedef  TYPE_2__ dtrace_enabling_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dtvs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probe_enable (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* dtrace_retained ; 

__attribute__((used)) static void
dtrace_enabling_prime(dtrace_state_t *state)
{
	dtrace_enabling_t *enab;
	int i;

	for (enab = dtrace_retained; enab != NULL; enab = enab->dten_next) {
		ASSERT(enab->dten_vstate->dtvs_state != NULL);

		if (enab->dten_vstate->dtvs_state != state)
			continue;

		/*
		 * We don't want to prime an enabling more than once, lest
		 * we allow a malicious user to induce resource exhaustion.
		 * (The ECBs that result from priming an enabling aren't
		 * leaked -- but they also aren't deallocated until the
		 * consumer state is destroyed.)
		 */
		if (enab->dten_primed)
			continue;

		for (i = 0; i < enab->dten_ndesc; i++) {
			enab->dten_current = enab->dten_desc[i];
			(void) dtrace_probe_enable(NULL, enab, NULL);
		}

		enab->dten_primed = 1;
	}
}