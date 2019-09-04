#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* dtps_provide ) (void*,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {TYPE_2__ dtpv_pops; void* dtpv_arg; struct TYPE_11__* dtpv_next; } ;
typedef  TYPE_3__ dtrace_provider_t ;
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
typedef  scalar_t__ dtrace_genid_t ;
struct TYPE_12__ {int dten_ndesc; TYPE_1__** dten_desc; struct TYPE_12__* dten_next; } ;
typedef  TYPE_4__ dtrace_enabling_t ;
struct TYPE_9__ {int /*<<< orphan*/  dted_probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_probe_provide (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 TYPE_4__* dtrace_retained ; 
 scalar_t__ dtrace_retained_gen ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_enabling_provide(dtrace_provider_t *prv)
{
	int i, all = 0;
	dtrace_probedesc_t desc;
        dtrace_genid_t gen;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&dtrace_provider_lock, LCK_MTX_ASSERT_OWNED);

	if (prv == NULL) {
		all = 1;
		prv = dtrace_provider;
	}

	do {
		dtrace_enabling_t *enab;
		void *parg = prv->dtpv_arg;

retry:
		gen = dtrace_retained_gen;
		for (enab = dtrace_retained; enab != NULL;
		    enab = enab->dten_next) {
			for (i = 0; i < enab->dten_ndesc; i++) {
				desc = enab->dten_desc[i]->dted_probe;
				lck_mtx_unlock(&dtrace_lock);
				prv->dtpv_pops.dtps_provide(parg, &desc);
				lck_mtx_lock(&dtrace_lock);
				/*
				 * Process the retained enablings again if
				 * they have changed while we weren't holding
				 * dtrace_lock.
				 */
				if (gen != dtrace_retained_gen)
					goto retry;
			}
		}
	} while (all && (prv = prv->dtpv_next) != NULL);

	lck_mtx_unlock(&dtrace_lock);
	dtrace_probe_provide(NULL, all ? NULL : prv);
	lck_mtx_lock(&dtrace_lock);
}