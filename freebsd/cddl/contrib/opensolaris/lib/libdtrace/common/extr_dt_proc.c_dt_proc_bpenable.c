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
struct TYPE_7__ {scalar_t__ dbp_active; int /*<<< orphan*/  dbp_instr; int /*<<< orphan*/  dbp_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dpr_proc; TYPE_2__ dpr_bps; int /*<<< orphan*/  dpr_lock; } ;
typedef  TYPE_1__ dt_proc_t ;
typedef  TYPE_2__ dt_bkpt_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DT_MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ Psetbkpt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_dprintf (char*) ; 
 TYPE_2__* dt_list_next (TYPE_2__*) ; 

__attribute__((used)) static void
dt_proc_bpenable(dt_proc_t *dpr)
{
	dt_bkpt_t *dbp;

	assert(DT_MUTEX_HELD(&dpr->dpr_lock));

	for (dbp = dt_list_next(&dpr->dpr_bps);
	    dbp != NULL; dbp = dt_list_next(dbp)) {
		if (!dbp->dbp_active && Psetbkpt(dpr->dpr_proc,
		    dbp->dbp_addr, &dbp->dbp_instr) == 0)
			dbp->dbp_active = B_TRUE;
	}

	dt_dprintf("breakpoints enabled\n");
}