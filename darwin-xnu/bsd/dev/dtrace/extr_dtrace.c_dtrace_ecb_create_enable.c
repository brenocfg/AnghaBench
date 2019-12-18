#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_9__ {scalar_t__ dtpr_gen; } ;
typedef  TYPE_2__ dtrace_probe_t ;
struct TYPE_10__ {TYPE_1__* dten_vstate; } ;
typedef  TYPE_3__ dtrace_enabling_t ;
struct TYPE_11__ {scalar_t__ dted_probegen; } ;
typedef  TYPE_4__ dtrace_ecbdesc_t ;
typedef  int /*<<< orphan*/  dtrace_ecb_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dtvs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DTRACE_MATCH_DONE ; 
 int DTRACE_MATCH_FAIL ; 
 int DTRACE_MATCH_NEXT ; 
 int /*<<< orphan*/ * dtrace_ecb_create (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ dtrace_ecb_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_ecb_create_enable(dtrace_probe_t *probe, void *arg1, void *arg2)
{
	dtrace_ecb_t *ecb;
	dtrace_enabling_t *enab = arg1;
	dtrace_ecbdesc_t *ep = arg2;
	dtrace_state_t *state = enab->dten_vstate->dtvs_state;

	ASSERT(state != NULL);

	if (probe != NULL && ep != NULL && probe->dtpr_gen < ep->dted_probegen) {
		/*
		 * This probe was created in a generation for which this
		 * enabling has previously created ECBs; we don't want to
		 * enable it again, so just kick out.
		 */
		return (DTRACE_MATCH_NEXT);
	}

	if ((ecb = dtrace_ecb_create(state, probe, enab)) == NULL)
		return (DTRACE_MATCH_DONE);

	if (dtrace_ecb_enable(ecb) < 0)
               return (DTRACE_MATCH_FAIL);
	
	return (DTRACE_MATCH_NEXT);
}