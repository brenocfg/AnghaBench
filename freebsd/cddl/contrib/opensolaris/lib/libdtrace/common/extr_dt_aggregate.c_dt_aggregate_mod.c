#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ dm_text_va; scalar_t__ dm_text_size; } ;
struct TYPE_6__ {TYPE_2__ dt_modlist; int /*<<< orphan*/ * dt_vector; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_module_t ;

/* Variables and functions */
 TYPE_2__* dt_list_next (TYPE_2__*) ; 

__attribute__((used)) static void
dt_aggregate_mod(dtrace_hdl_t *dtp, uint64_t *data)
{
	uint64_t *pc = data;
	dt_module_t *dmp;

	if (dtp->dt_vector != NULL) {
		/*
		 * We don't have a way of just getting the module for a
		 * vectored open, and it doesn't seem to be worth defining
		 * one.  This means that use of mod() won't get true
		 * aggregation in the postmortem case (some modules may
		 * appear more than once in aggregation output).  It seems
		 * unlikely that anyone will ever notice or care...
		 */
		return;
	}

	for (dmp = dt_list_next(&dtp->dt_modlist); dmp != NULL;
	    dmp = dt_list_next(dmp)) {
		if (*pc - dmp->dm_text_va < dmp->dm_text_size) {
			*pc = dmp->dm_text_va;
			return;
		}
	}
}