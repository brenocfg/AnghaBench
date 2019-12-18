#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zoneid_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  dtrace_state_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dta_enabling; } ;

/* Variables and functions */
 scalar_t__ DTRACE_DOF_MODE_LAZY_OFF ; 
 scalar_t__ DTRACE_DOF_MODE_LAZY_ON ; 
 scalar_t__ DTRACE_KERNEL_SYMBOLS_FROM_KERNEL ; 
 scalar_t__ DTRACE_KERNEL_SYMBOLS_FROM_USERSPACE ; 
 scalar_t__ DTRACE_PRIV_NONE ; 
 int EACCES ; 
 int EBUSY ; 
 int /*<<< orphan*/  KDI_DTSET_DTRACE_ACTIVATE ; 
 int /*<<< orphan*/  KDI_DTSET_DTRACE_DEACTIVATE ; 
 int PROC_ALLPROCLIST ; 
 int PROC_NOWAITTRANS ; 
 int /*<<< orphan*/  cpu_lock ; 
 TYPE_1__ dtrace_anon ; 
 int /*<<< orphan*/  dtrace_cred2priv (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_dof_mode ; 
 int /*<<< orphan*/  dtrace_dof_mode_lock ; 
 scalar_t__ dtrace_kernel_symbol_mode ; 
 int /*<<< orphan*/  dtrace_lazy_dofs_proc_iterate_doit ; 
 int /*<<< orphan*/  dtrace_lazy_dofs_proc_iterate_filter ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_membar_producer () ; 
 scalar_t__ dtrace_opens ; 
 int /*<<< orphan*/  dtrace_probe_provide (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int dtrace_state_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fasttrap_init () ; 
 scalar_t__ kdi_dtrace_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive_to_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_iterate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_open(dev_t *devp, int flag, int otyp, cred_t *cred_p)
{
#pragma unused(flag, otyp)
	dtrace_state_t *state;
	uint32_t priv;
	uid_t uid;
	zoneid_t zoneid;
	int rv;

	/* APPLE: Darwin puts Helper on its own major device. */

	/*
	 * If no DTRACE_PRIV_* bits are set in the credential, then the
	 * caller lacks sufficient permission to do anything with DTrace.
	 */
	dtrace_cred2priv(cred_p, &priv, &uid, &zoneid);
	if (priv == DTRACE_PRIV_NONE)
		return (EACCES);

	/*
	 * APPLE NOTE: We delay the initialization of fasttrap as late as possible.
	 * It certainly can't be later than now!
	 */
	fasttrap_init();

	/*
	 * Ask all providers to provide all their probes.
	 */
	lck_mtx_lock(&dtrace_provider_lock);
	dtrace_probe_provide(NULL, NULL);
	lck_mtx_unlock(&dtrace_provider_lock);

	lck_mtx_lock(&cpu_lock);
	lck_mtx_lock(&dtrace_lock);
	dtrace_opens++;
	dtrace_membar_producer();

#ifdef illumos
	/*
	 * If the kernel debugger is active (that is, if the kernel debugger
	 * modified text in some way), we won't allow the open.
	 */
	if (kdi_dtrace_set(KDI_DTSET_DTRACE_ACTIVATE) != 0) {
		dtrace_opens--;
		lck_mtx_unlock(&dtrace_lock);
		lck_mtx_unlock(&cpu_lock);
		return (EBUSY);
	}
#endif

	rv = dtrace_state_create(devp, cred_p, &state);
	lck_mtx_unlock(&cpu_lock);

	if (rv != 0 || state == NULL) {
		if (--dtrace_opens == 0 && dtrace_anon.dta_enabling == NULL) {
#ifdef illumos
			(void) kdi_dtrace_set(KDI_DTSET_DTRACE_DEACTIVATE);
#endif
		}
		lck_mtx_unlock(&dtrace_lock);
		/* propagate EAGAIN or ERESTART */
		return (rv);
	}
	
	lck_mtx_unlock(&dtrace_lock);

	lck_rw_lock_exclusive(&dtrace_dof_mode_lock);

	/*
	 * If we are currently lazy, transition states.
	 *
	 * Unlike dtrace_close, we do not need to check the
	 * value of dtrace_opens, as any positive value (and
	 * we count as 1) means we transition states.
	 */
	if (dtrace_dof_mode == DTRACE_DOF_MODE_LAZY_ON) {
		dtrace_dof_mode = DTRACE_DOF_MODE_LAZY_OFF;
		/*
		 * We do not need to hold the exclusive lock while processing
		 * DOF on processes. We do need to make sure the mode does not get
		 * changed to DTRACE_DOF_MODE_LAZY_ON during that stage though
		 * (which should not happen anyway since it only happens in
		 * dtrace_close). There is no way imcomplete USDT probes can be
		 * activate by any DTrace clients here since they all have to
		 * call dtrace_open and be blocked on dtrace_dof_mode_lock
		 */
		lck_rw_lock_exclusive_to_shared(&dtrace_dof_mode_lock);
		/*
		 * Iterate all existing processes and load lazy dofs.
		 */
		proc_iterate(PROC_ALLPROCLIST | PROC_NOWAITTRANS,
			     dtrace_lazy_dofs_proc_iterate_doit,
			     NULL,
			     dtrace_lazy_dofs_proc_iterate_filter,
			     NULL);

		lck_rw_unlock_shared(&dtrace_dof_mode_lock);
	}
	else {
		lck_rw_unlock_exclusive(&dtrace_dof_mode_lock);
	}


	/*
	 * Update kernel symbol state.
	 *
	 * We must own the provider and dtrace locks. 
	 *
	 * NOTE! It may appear there is a race by setting this value so late
	 * after dtrace_probe_provide. However, any kext loaded after the
	 * call to probe provide and before we set LAZY_OFF will be marked as
	 * eligible for symbols from userspace. The same dtrace that is currently
	 * calling dtrace_open() (this call!) will get a list of kexts needing
	 * symbols and fill them in, thus closing the race window.
	 *
	 * We want to set this value only after it certain it will succeed, as
	 * this significantly reduces the complexity of error exits.
	 */
	lck_mtx_lock(&dtrace_lock);
	if (dtrace_kernel_symbol_mode == DTRACE_KERNEL_SYMBOLS_FROM_USERSPACE) {
		dtrace_kernel_symbol_mode = DTRACE_KERNEL_SYMBOLS_FROM_KERNEL;
	}
	lck_mtx_unlock(&dtrace_lock);

	return (0);
}