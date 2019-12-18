#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dtvs_nglobals; int dtvs_ntlocals; int dtvs_nlocals; int /*<<< orphan*/ * dtvs_locals; int /*<<< orphan*/ * dtvs_tlocals; int /*<<< orphan*/ * dtvs_globals; } ;
typedef  TYPE_1__ dtrace_vstate_t ;
typedef  int /*<<< orphan*/  dtrace_statvar_t ;
typedef  int /*<<< orphan*/  dtrace_difv_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dtrace_vstate_fini(dtrace_vstate_t *vstate)
{
	/*
	 * Logical XOR, where are you?
	 */
	ASSERT((vstate->dtvs_nglobals == 0) ^ (vstate->dtvs_globals != NULL));

	if (vstate->dtvs_nglobals > 0) {
		kmem_free(vstate->dtvs_globals, vstate->dtvs_nglobals *
		    sizeof (dtrace_statvar_t *));
	}

	if (vstate->dtvs_ntlocals > 0) {
		kmem_free(vstate->dtvs_tlocals, vstate->dtvs_ntlocals *
		    sizeof (dtrace_difv_t));
	}

	ASSERT((vstate->dtvs_nlocals == 0) ^ (vstate->dtvs_locals != NULL));

	if (vstate->dtvs_nlocals > 0) {
		kmem_free(vstate->dtvs_locals, vstate->dtvs_nlocals *
		    sizeof (dtrace_statvar_t *));
	}
}