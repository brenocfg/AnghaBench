#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  p_dtrace_probes; } ;
typedef  TYPE_1__ proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_11__ {scalar_t__ ftp_rcount; scalar_t__ ftp_ccount; scalar_t__ ftp_mcount; int /*<<< orphan*/  ftp_cmtx; int /*<<< orphan*/  ftp_mtx; TYPE_9__* ftp_proc; int /*<<< orphan*/  ftp_retired; int /*<<< orphan*/  ftp_pid; } ;
typedef  TYPE_2__ fasttrap_provider_t ;
struct TYPE_12__ {scalar_t__ ftpc_acount; scalar_t__ ftpc_rcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  atomic_add_64 (scalar_t__*,int) ; 
 int /*<<< orphan*/  fasttrap_lck_grp ; 
 int /*<<< orphan*/  fasttrap_proc_release (TYPE_9__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
fasttrap_provider_free(fasttrap_provider_t *provider)
{
	pid_t pid = provider->ftp_pid;
	proc_t *p;

	/*
	 * There need to be no associated enabled probes, no consumers
	 * creating probes, and no meta providers referencing this provider.
	 */
	ASSERT(provider->ftp_rcount == 0);
	ASSERT(provider->ftp_ccount == 0);
	ASSERT(provider->ftp_mcount == 0);

	/*
	 * If this provider hasn't been retired, we need to explicitly drop the
	 * count of active providers on the associated process structure.
	 */
	if (!provider->ftp_retired) {
		atomic_add_64(&provider->ftp_proc->ftpc_acount, -1);
		ASSERT(provider->ftp_proc->ftpc_acount <
		provider->ftp_proc->ftpc_rcount);
	}

	fasttrap_proc_release(provider->ftp_proc);

	/*
	 * APPLE NOTE:  explicit lock management. Not 100% certain we need this, the
	 * memory is freed even without the destroy. Maybe accounting cleanup?
	 */
	lck_mtx_destroy(&provider->ftp_mtx, fasttrap_lck_grp);
	lck_mtx_destroy(&provider->ftp_cmtx, fasttrap_lck_grp);

	kmem_free(provider, sizeof (fasttrap_provider_t));

	/*
	 * Decrement p_dtrace_probes on the process whose provider we're
	 * freeing. We don't have to worry about clobbering somone else's
	 * modifications to it because we have locked the bucket that
	 * corresponds to this process's hash chain in the provider hash
	 * table. Don't sweat it if we can't find the process.
	 */
	if ((p = proc_find(pid)) == NULL) {
		return;
	}

	proc_lock(p);
	p->p_dtrace_probes--;
	proc_unlock(p);
	
	proc_rele(p);
}