#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_toxrange_t ;
struct TYPE_4__ {scalar_t__ dts_necbs; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_provider_id_t ;
typedef  int /*<<< orphan*/  dtrace_probe_t ;
typedef  int /*<<< orphan*/  dtrace_anon_t ;
typedef  int /*<<< orphan*/  dev_info_t ;
typedef  int ddi_detach_cmd_t ;
typedef  int /*<<< orphan*/  cpu_setup_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  DDI_DETACH 129 
 int DDI_FAILURE ; 
 int DDI_SUCCESS ; 
#define  DDI_SUSPEND 128 
 int /*<<< orphan*/  KDI_DTSET_DTRACE_DEACTIVATE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddi_soft_state_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_anon ; 
 TYPE_1__* dtrace_anon_grab () ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/ * dtrace_byfunc ; 
 int /*<<< orphan*/ * dtrace_bymod ; 
 int /*<<< orphan*/ * dtrace_byname ; 
 int /*<<< orphan*/ * dtrace_byprov ; 
 int /*<<< orphan*/ * dtrace_cpu_init ; 
 scalar_t__ dtrace_cpu_setup ; 
 int /*<<< orphan*/ * dtrace_cpustart_fini ; 
 int /*<<< orphan*/ * dtrace_cpustart_init ; 
 int /*<<< orphan*/ * dtrace_debugger_fini ; 
 int /*<<< orphan*/ * dtrace_debugger_init ; 
 int /*<<< orphan*/ * dtrace_devi ; 
 int /*<<< orphan*/  dtrace_hash_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_helpers ; 
 int /*<<< orphan*/ * dtrace_helpers_cleanup ; 
 int /*<<< orphan*/ * dtrace_helpers_fork ; 
 int /*<<< orphan*/ * dtrace_helptrace_buffer ; 
 int dtrace_helptrace_bufsize ; 
 scalar_t__ dtrace_helptrace_enabled ; 
 int /*<<< orphan*/ * dtrace_kreloc_fini ; 
 int /*<<< orphan*/ * dtrace_kreloc_init ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/ * dtrace_modload ; 
 int /*<<< orphan*/ * dtrace_modunload ; 
 int dtrace_nprobes ; 
 scalar_t__ dtrace_opens ; 
 int /*<<< orphan*/ * dtrace_probes ; 
 int /*<<< orphan*/ * dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/ * dtrace_retained ; 
 int /*<<< orphan*/  dtrace_softstate ; 
 int /*<<< orphan*/  dtrace_state_cache ; 
 int /*<<< orphan*/  dtrace_state_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/ * dtrace_strings ; 
 int /*<<< orphan*/ * dtrace_taskq ; 
 int /*<<< orphan*/ * dtrace_toxrange ; 
 scalar_t__ dtrace_toxranges ; 
 int dtrace_toxranges_max ; 
 scalar_t__ dtrace_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_vtime_references ; 
 int /*<<< orphan*/  kdi_dtrace_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_cpu_setup_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	dtrace_state_t *state;

	switch (cmd) {
	case DDI_DETACH:
		break;

	case DDI_SUSPEND:
		return (DDI_SUCCESS);

	default:
		return (DDI_FAILURE);
	}

	lck_mtx_lock(&cpu_lock);
	lck_mtx_lock(&dtrace_provider_lock);
	lck_mtx_lock(&dtrace_lock);

	ASSERT(dtrace_opens == 0);

	if (dtrace_helpers > 0) {
		lck_mtx_unlock(&dtrace_lock);
		lck_mtx_unlock(&dtrace_provider_lock);
		lck_mtx_unlock(&cpu_lock);
		return (DDI_FAILURE);
	}

	if (dtrace_unregister((dtrace_provider_id_t)dtrace_provider) != 0) {
		lck_mtx_unlock(&dtrace_lock);
		lck_mtx_unlock(&dtrace_provider_lock);
		lck_mtx_unlock(&cpu_lock);
		return (DDI_FAILURE);
	}

	dtrace_provider = NULL;

	if ((state = dtrace_anon_grab()) != NULL) {
		/*
		 * If there were ECBs on this state, the provider should
		 * have not been allowed to detach; assert that there is
		 * none.
		 */
		ASSERT(state->dts_necbs == 0);
		dtrace_state_destroy(state);

		/*
		 * If we're being detached with anonymous state, we need to
		 * indicate to the kernel debugger that DTrace is now inactive.
		 */
		(void) kdi_dtrace_set(KDI_DTSET_DTRACE_DEACTIVATE);
	}

	bzero(&dtrace_anon, sizeof (dtrace_anon_t));
	unregister_cpu_setup_func((cpu_setup_func_t *)dtrace_cpu_setup, NULL);
	dtrace_cpu_init = NULL;
	dtrace_helpers_cleanup = NULL;
	dtrace_helpers_fork = NULL;
	dtrace_cpustart_init = NULL;
	dtrace_cpustart_fini = NULL;
	dtrace_debugger_init = NULL;
	dtrace_debugger_fini = NULL;
	dtrace_kreloc_init = NULL;
	dtrace_kreloc_fini = NULL;
	dtrace_modload = NULL;
	dtrace_modunload = NULL;

	lck_mtx_unlock(&cpu_lock);

	if (dtrace_helptrace_enabled) {
		kmem_free(dtrace_helptrace_buffer, dtrace_helptrace_bufsize);
		dtrace_helptrace_buffer = NULL;
	}

	kmem_free(dtrace_probes, dtrace_nprobes * sizeof (dtrace_probe_t *));
	dtrace_probes = NULL;
	dtrace_nprobes = 0;

	dtrace_hash_destroy(dtrace_strings);
	dtrace_hash_destroy(dtrace_byprov);
	dtrace_hash_destroy(dtrace_bymod);
	dtrace_hash_destroy(dtrace_byfunc);
	dtrace_hash_destroy(dtrace_byname);
	dtrace_strings = NULL;
	dtrace_byprov = NULL;
	dtrace_bymod = NULL;
	dtrace_byfunc = NULL;
	dtrace_byname = NULL;

	kmem_cache_destroy(dtrace_state_cache);
	vmem_destroy(dtrace_arena);

	if (dtrace_toxrange != NULL) {
		kmem_free(dtrace_toxrange,
		    dtrace_toxranges_max * sizeof (dtrace_toxrange_t));
		dtrace_toxrange = NULL;
		dtrace_toxranges = 0;
		dtrace_toxranges_max = 0;
	}

	ddi_remove_minor_node(dtrace_devi, NULL);
	dtrace_devi = NULL;

	ddi_soft_state_fini(&dtrace_softstate);

	ASSERT(dtrace_vtime_references == 0);
	ASSERT(dtrace_opens == 0);
	ASSERT(dtrace_retained == NULL);

	lck_mtx_unlock(&dtrace_lock);
	lck_mtx_unlock(&dtrace_provider_lock);

#ifdef illumos
	/*
	 * We don't destroy the task queue until after we have dropped our
	 * locks (taskq_destroy() may block on running tasks).  To prevent
	 * attempting to do work after we have effectively detached but before
	 * the task queue has been destroyed, all tasks dispatched via the
	 * task queue must check that DTrace is still attached before
	 * performing any operation.
	 */
	taskq_destroy(dtrace_taskq);
	dtrace_taskq = NULL;
#endif

	return (DDI_SUCCESS);
}