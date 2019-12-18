#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dbp_instr; int /*<<< orphan*/  dbp_addr; scalar_t__ dbp_active; } ;
struct TYPE_9__ {int /*<<< orphan*/  dpr_hdl; TYPE_2__ dpr_bps; int /*<<< orphan*/  dpr_proc; int /*<<< orphan*/  dpr_lock; } ;
typedef  TYPE_1__ dt_proc_t ;
typedef  TYPE_2__ dt_bkpt_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int PS_LOST ; 
 int PS_UNDEAD ; 
 int /*<<< orphan*/  Pdelbkpt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Pstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_list_delete (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* dt_list_next (TYPE_2__*) ; 

__attribute__((used)) static void
dt_proc_bpdestroy(dt_proc_t *dpr, int delbkpts)
{
	int state = Pstate(dpr->dpr_proc);
	dt_bkpt_t *dbp, *nbp;

	assert(DT_MUTEX_HELD(&dpr->dpr_lock));

	for (dbp = dt_list_next(&dpr->dpr_bps); dbp != NULL; dbp = nbp) {
		if (delbkpts && dbp->dbp_active &&
		    state != PS_LOST && state != PS_UNDEAD) {
			(void) Pdelbkpt(dpr->dpr_proc,
			    dbp->dbp_addr, dbp->dbp_instr);
		}
		nbp = dt_list_next(dbp);
		dt_list_delete(&dpr->dpr_bps, dbp);
		dt_free(dpr->dpr_hdl, dbp);
	}
}