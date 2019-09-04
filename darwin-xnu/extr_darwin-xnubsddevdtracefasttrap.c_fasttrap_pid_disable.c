#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_4__ {scalar_t__ ftp_rcount; int ftp_marked; int /*<<< orphan*/  ftp_mtx; scalar_t__ ftp_retired; } ;
typedef  TYPE_1__ fasttrap_provider_t ;
struct TYPE_5__ {scalar_t__ ftp_id; scalar_t__ ftp_enabled; scalar_t__ ftp_ntps; int /*<<< orphan*/  ftp_pid; TYPE_1__* ftp_prov; } ;
typedef  TYPE_2__ fasttrap_probe_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FASTTRAP_CLEANUP_PROVIDER ; 
 int /*<<< orphan*/ * PROC_NULL ; 
 int /*<<< orphan*/  fasttrap_disable_callbacks () ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_tracepoint_disable (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sprlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_pid_disable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg, id)
	fasttrap_probe_t *probe = parg;
	fasttrap_provider_t *provider = probe->ftp_prov;
	proc_t *p;
	int i, whack = 0;

	ASSERT(id == probe->ftp_id);

	/*
	 * We won't be able to acquire a /proc-esque lock on the process
	 * iff the process is dead and gone. In this case, we rely on the
	 * provider lock as a point of mutual exclusion to prevent other
	 * DTrace consumers from disabling this probe.
	 */
	if ((p = sprlock(probe->ftp_pid)) != PROC_NULL) {
		// ASSERT(!(p->p_flag & SVFORK));
		proc_unlock(p);
	}

	lck_mtx_lock(&provider->ftp_mtx);

	/*
	 * Disable all the associated tracepoints (for fully enabled probes).
	 */
	if (probe->ftp_enabled) {
		for (i = 0; i < (int)probe->ftp_ntps; i++) {
			fasttrap_tracepoint_disable(p, probe, i);
		}
	}

	ASSERT(provider->ftp_rcount > 0);
	provider->ftp_rcount--;

	if (p != NULL) {
		/*
		 * Even though we may not be able to remove it entirely, we
		 * mark this retired provider to get a chance to remove some
		 * of the associated probes.
		 */
		if (provider->ftp_retired && !provider->ftp_marked)
			whack = provider->ftp_marked = 1;
		lck_mtx_unlock(&provider->ftp_mtx);

		proc_lock(p);
		sprunlock(p);
	} else {
		/*
		 * If the process is dead, we're just waiting for the
		 * last probe to be disabled to be able to free it.
		 */
		if (provider->ftp_rcount == 0 && !provider->ftp_marked)
			whack = provider->ftp_marked = 1;
		lck_mtx_unlock(&provider->ftp_mtx);
	}

	if (whack) {
		fasttrap_pid_cleanup(FASTTRAP_CLEANUP_PROVIDER);
	}

	if (!probe->ftp_enabled)
		return;

	probe->ftp_enabled = 0;

	// ASSERT(MUTEX_HELD(&cpu_lock));
	fasttrap_disable_callbacks();
}