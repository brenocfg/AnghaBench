#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_pid; } ;
typedef  TYPE_2__ proc_t ;
struct TYPE_10__ {int dthps_deferred; size_t dthps_nprovs; TYPE_1__** dthps_provs; struct TYPE_10__* dthps_prev; struct TYPE_10__* dthps_next; int /*<<< orphan*/  dthps_pid; } ;
typedef  TYPE_3__ dtrace_helpers_t ;
typedef  int /*<<< orphan*/  dof_helper_t ;
struct TYPE_8__ {int /*<<< orphan*/  dthp_prov; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_attached () ; 
 TYPE_3__* dtrace_deferred_pid ; 
 int /*<<< orphan*/  dtrace_helper_provide (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 int /*<<< orphan*/ * dtrace_meta_pid ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_helper_provider_register(proc_t *p, dtrace_helpers_t *help,
    dof_helper_t *dofhp)
{
	LCK_MTX_ASSERT(&dtrace_meta_lock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_NOTOWNED);

	lck_mtx_lock(&dtrace_lock);

	if (!dtrace_attached() || dtrace_meta_pid == NULL) {
		/*
		 * If the dtrace module is loaded but not attached, or if
		 * there aren't isn't a meta provider registered to deal with
		 * these provider descriptions, we need to postpone creating
		 * the actual providers until later.
		 */

		if (help->dthps_next == NULL && help->dthps_prev == NULL &&
		    dtrace_deferred_pid != help) {
			help->dthps_deferred = 1;
			help->dthps_pid = p->p_pid;
			help->dthps_next = dtrace_deferred_pid;
			help->dthps_prev = NULL;
			if (dtrace_deferred_pid != NULL)
				dtrace_deferred_pid->dthps_prev = help;
			dtrace_deferred_pid = help;
		}

		lck_mtx_unlock(&dtrace_lock);

	} else if (dofhp != NULL) {
		/*
		 * If the dtrace module is loaded and we have a particular
		 * helper provider description, pass that off to the
		 * meta provider.
		 */

		lck_mtx_unlock(&dtrace_lock);

		dtrace_helper_provide(dofhp, p);

	} else {
		/*
		 * Otherwise, just pass all the helper provider descriptions
		 * off to the meta provider.
		 */

		uint_t i;
		lck_mtx_unlock(&dtrace_lock);

		for (i = 0; i < help->dthps_nprovs; i++) {
			dtrace_helper_provide(&help->dthps_provs[i]->dthp_prov,
				p);
		}
	}
}