#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  minor_t ;
struct TYPE_5__ {struct TYPE_5__* dts_anon; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dta_enabling; int /*<<< orphan*/ * dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_DOF_MODE_LAZY_OFF ; 
 scalar_t__ DTRACE_DOF_MODE_LAZY_ON ; 
 scalar_t__ DTRACE_KERNEL_SYMBOLS_FROM_KERNEL ; 
 scalar_t__ DTRACE_KERNEL_SYMBOLS_FROM_USERSPACE ; 
 int /*<<< orphan*/  KDI_DTSET_DTRACE_DEACTIVATE ; 
 int /*<<< orphan*/  cpu_lock ; 
 TYPE_4__ dtrace_anon ; 
 scalar_t__ dtrace_dof_mode ; 
 int /*<<< orphan*/  dtrace_dof_mode_lock ; 
 scalar_t__ dtrace_kernel_symbol_mode ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_module_unloaded (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_opens ; 
 int /*<<< orphan*/  dtrace_state_destroy (TYPE_1__*) ; 
 TYPE_1__* dtrace_state_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdi_dtrace_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_close(dev_t dev, int flag, int otyp, cred_t *cred_p)
{
#pragma unused(flag, otyp, cred_p) /* __APPLE__ */
	minor_t minor = getminor(dev);
	dtrace_state_t *state;

	/* APPLE NOTE: Darwin puts Helper on its own major device. */
	state = dtrace_state_get(minor);

	lck_mtx_lock(&cpu_lock);
	lck_mtx_lock(&dtrace_lock);

	if (state->dts_anon) {
		/*
		 * There is anonymous state. Destroy that first.
		 */
		ASSERT(dtrace_anon.dta_state == NULL);
		dtrace_state_destroy(state->dts_anon);
	}

	dtrace_state_destroy(state);
	ASSERT(dtrace_opens > 0);

	/*
	 * Only relinquish control of the kernel debugger interface when there
	 * are no consumers and no anonymous enablings.
	 */
	if (--dtrace_opens == 0 && dtrace_anon.dta_enabling == NULL) {
#ifdef illumos
		(void) kdi_dtrace_set(KDI_DTSET_DTRACE_DEACTIVATE);
#endif
	}

	lck_mtx_unlock(&dtrace_lock);
	lck_mtx_unlock(&cpu_lock);

	/*
	 * Lock ordering requires the dof mode lock be taken before
	 * the dtrace_lock.
	 */
	lck_rw_lock_exclusive(&dtrace_dof_mode_lock);
	lck_mtx_lock(&dtrace_lock);
	
	if (dtrace_opens == 0) {
		/*
		 * If we are currently lazy-off, and this is the last close, transition to
		 * lazy state.
		 */
		if (dtrace_dof_mode == DTRACE_DOF_MODE_LAZY_OFF) {
			dtrace_dof_mode = DTRACE_DOF_MODE_LAZY_ON;
		}

		/*
		 * If we are the last dtrace client, switch back to lazy (from userspace) symbols
		 */
		if (dtrace_kernel_symbol_mode == DTRACE_KERNEL_SYMBOLS_FROM_KERNEL) {
			dtrace_kernel_symbol_mode = DTRACE_KERNEL_SYMBOLS_FROM_USERSPACE;
		}
	}
	
	lck_mtx_unlock(&dtrace_lock);
	lck_rw_unlock_exclusive(&dtrace_dof_mode_lock);
	
	/*
	 * Kext probes may be retained past the end of the kext's lifespan. The
	 * probes are kept until the last reference to them has been removed.
	 * Since closing an active dtrace context is likely to drop that last reference,
	 * lets take a shot at cleaning out the orphaned probes now.
	 */
	dtrace_module_unloaded(NULL);

	return (0);
}