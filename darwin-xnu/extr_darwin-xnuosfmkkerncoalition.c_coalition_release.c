#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* coalition_t ;
struct TYPE_7__ {scalar_t__ ref_count; int termrequested; int terminated; scalar_t__ active_count; int reaped; scalar_t__ focal_task_count; scalar_t__ nonfocal_task_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_COALITION ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_COALITION_FREE ; 
 int /*<<< orphan*/  ac ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  coal_call (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  coal_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalition_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_zone ; 
 int /*<<< orphan*/  coalitions_lck_grp ; 
 int /*<<< orphan*/  dealloc ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rc ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
coalition_release(coalition_t coal)
{
	/* TODO: This can be done with atomics. */
	coalition_lock(coal);
	coal->ref_count--;

#if COALITION_DEBUG
	uint32_t rc = coal->ref_count;
	uint32_t ac = coal->active_count;
#endif /* COALITION_DEBUG */

	coal_dbg("id:%llu type:%s ref_count:%u active_count:%u%s",
		 coal->id, coal_type_str(coal->type), rc, ac,
		 rc <= 0 ? ", will deallocate now" : "");

	if (coal->ref_count > 0) {
		coalition_unlock(coal);
		return;
	}

	assert(coal->termrequested);
	assert(coal->terminated);
	assert(coal->active_count == 0);
	assert(coal->reaped);
	assert(coal->focal_task_count == 0);
	assert(coal->nonfocal_task_count == 0);
	KDBG_RELEASE(MACHDBG_CODE(DBG_MACH_COALITION, MACH_COALITION_FREE),
		coal->id, coal->type);

	coal_call(coal, dealloc);

	coalition_unlock(coal);

	lck_mtx_destroy(&coal->lock, &coalitions_lck_grp);

	zfree(coalition_zone, coal);
}