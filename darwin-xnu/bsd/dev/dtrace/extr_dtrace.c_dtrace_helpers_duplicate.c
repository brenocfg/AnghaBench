#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_13__ {TYPE_3__* p_dtrace_helpers; } ;
typedef  TYPE_2__ proc_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_14__ {scalar_t__ dthps_nprovs; scalar_t__ dthps_maxprovs; TYPE_1__** dthps_provs; TYPE_4__** dthps_actions; int /*<<< orphan*/  dthps_vstate; int /*<<< orphan*/  dthps_generation; } ;
typedef  TYPE_3__ dtrace_helpers_t ;
typedef  int /*<<< orphan*/  dtrace_helper_provider_t ;
struct TYPE_15__ {int dtha_nactions; struct TYPE_15__* dtha_next; int /*<<< orphan*/ ** dtha_actions; int /*<<< orphan*/ * dtha_predicate; int /*<<< orphan*/  dtha_generation; } ;
typedef  TYPE_4__ dtrace_helper_action_t ;
typedef  int /*<<< orphan*/  dtrace_difo_t ;
struct TYPE_12__ {int /*<<< orphan*/  dthp_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t DTRACE_NHELPER_ACTIONS ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/ * dtrace_difo_duplicate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_helper_provider_register (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_helpers ; 
 TYPE_3__* dtrace_helpers_create (TYPE_2__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 void* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_helpers_duplicate(proc_t *from, proc_t *to)
{
	dtrace_helpers_t *help, *newhelp;
	dtrace_helper_action_t *helper, *new, *last;
	dtrace_difo_t *dp;
	dtrace_vstate_t *vstate;
	uint_t i;
	int j, sz, hasprovs = 0;

	lck_mtx_lock(&dtrace_meta_lock);
	lck_mtx_lock(&dtrace_lock);
	ASSERT(from->p_dtrace_helpers != NULL);
	ASSERT(dtrace_helpers > 0);

	help = from->p_dtrace_helpers;
	newhelp = dtrace_helpers_create(to);
	ASSERT(to->p_dtrace_helpers != NULL);

	newhelp->dthps_generation = help->dthps_generation;
	vstate = &newhelp->dthps_vstate;

	/*
	 * Duplicate the helper actions.
	 */
	for (i = 0; i < DTRACE_NHELPER_ACTIONS; i++) {
		if ((helper = help->dthps_actions[i]) == NULL)
			continue;

		for (last = NULL; helper != NULL; helper = helper->dtha_next) {
			new = kmem_zalloc(sizeof (dtrace_helper_action_t),
			    KM_SLEEP);
			new->dtha_generation = helper->dtha_generation;

			if ((dp = helper->dtha_predicate) != NULL) {
				dp = dtrace_difo_duplicate(dp, vstate);
				new->dtha_predicate = dp;
			}

			new->dtha_nactions = helper->dtha_nactions;
			sz = sizeof (dtrace_difo_t *) * new->dtha_nactions;
			new->dtha_actions = kmem_alloc(sz, KM_SLEEP);

			for (j = 0; j < new->dtha_nactions; j++) {
				dtrace_difo_t *dpj = helper->dtha_actions[j];

				ASSERT(dpj != NULL);
				dpj = dtrace_difo_duplicate(dpj, vstate);
				new->dtha_actions[j] = dpj;
			}

			if (last != NULL) {
				last->dtha_next = new;
			} else {
				newhelp->dthps_actions[i] = new;
			}

			last = new;
		}
	}

	/*
	 * Duplicate the helper providers and register them with the
	 * DTrace framework.
	 */
	if (help->dthps_nprovs > 0) {
		newhelp->dthps_nprovs = help->dthps_nprovs;
		newhelp->dthps_maxprovs = help->dthps_nprovs;
		newhelp->dthps_provs = kmem_alloc(newhelp->dthps_nprovs *
		    sizeof (dtrace_helper_provider_t *), KM_SLEEP);
		for (i = 0; i < newhelp->dthps_nprovs; i++) {
			newhelp->dthps_provs[i] = help->dthps_provs[i];
			newhelp->dthps_provs[i]->dthp_ref++;
		}

		hasprovs = 1;
	}

	lck_mtx_unlock(&dtrace_lock);

	if (hasprovs)
		dtrace_helper_provider_register(to, newhelp, NULL);

	lck_mtx_unlock(&dtrace_meta_lock);
}