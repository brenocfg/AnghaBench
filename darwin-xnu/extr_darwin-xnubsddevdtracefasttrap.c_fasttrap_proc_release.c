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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_6__ {scalar_t__ ftpc_rcount; scalar_t__ ftpc_acount; int /*<<< orphan*/  ftpc_mtx; struct TYPE_6__* ftpc_next; int /*<<< orphan*/  ftpc_pid; } ;
typedef  TYPE_1__ fasttrap_proc_t ;
struct TYPE_7__ {int /*<<< orphan*/  ftb_mtx; int /*<<< orphan*/  ftb_data; } ;
typedef  TYPE_2__ fasttrap_bucket_t ;
struct TYPE_8__ {TYPE_2__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t FASTTRAP_PROCS_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_lck_grp ; 
 TYPE_4__ fasttrap_procs ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_proc_release(fasttrap_proc_t *proc)
{
	fasttrap_bucket_t *bucket;
	fasttrap_proc_t *fprc, **fprcp;
	pid_t pid = proc->ftpc_pid;

	lck_mtx_lock(&proc->ftpc_mtx);

	ASSERT(proc->ftpc_rcount != 0);
	ASSERT(proc->ftpc_acount <= proc->ftpc_rcount);

	if (--proc->ftpc_rcount != 0) {
		lck_mtx_unlock(&proc->ftpc_mtx);
		return;
	}

	lck_mtx_unlock(&proc->ftpc_mtx);

	/*
	 * There should definitely be no live providers associated with this
	 * process at this point.
	 */
	 ASSERT(proc->ftpc_acount == 0);

	bucket = &fasttrap_procs.fth_table[FASTTRAP_PROCS_INDEX(pid)];
	lck_mtx_lock(&bucket->ftb_mtx);

	fprcp = (fasttrap_proc_t **)&bucket->ftb_data;
	while ((fprc = *fprcp) != NULL) {
		if (fprc == proc)
			break;

		fprcp = &fprc->ftpc_next;
	}

	/*
	 * Something strange has happened if we can't find the proc.
	 */
	ASSERT(fprc != NULL);

	*fprcp = fprc->ftpc_next;

	lck_mtx_unlock(&bucket->ftb_mtx);

	/*
	 * APPLE NOTE: explicit lock management. Not 100% certain we need this, the
	 * memory is freed even without the destroy. Maybe accounting cleanup?
	 */
	lck_mtx_destroy(&fprc->ftpc_mtx, fasttrap_lck_grp);

	kmem_free(fprc, sizeof (fasttrap_proc_t));
}