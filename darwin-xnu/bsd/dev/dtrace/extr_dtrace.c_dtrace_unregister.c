#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int (* dtps_enable ) (void*,dtrace_id_t,void*) ;int /*<<< orphan*/  (* dtps_destroy ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {scalar_t__ dtpv_ecb_count; int /*<<< orphan*/  dtpv_name; struct TYPE_17__* dtpv_next; int /*<<< orphan*/  dtpv_arg; TYPE_2__ dtpv_pops; int /*<<< orphan*/  dtpv_probe_count; int /*<<< orphan*/  dtpv_defunct; } ;
typedef  TYPE_3__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_18__ {int dtpr_id; int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; int /*<<< orphan*/  dtpr_arg; struct TYPE_18__* dtpr_nextmod; TYPE_3__* dtpr_provider; } ;
typedef  TYPE_4__ dtrace_probe_t ;
struct TYPE_15__ {scalar_t__ dts_necbs; } ;
struct TYPE_14__ {TYPE_1__* dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_4__** DTRACE_HASHNEXT (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 TYPE_11__ dtrace_anon ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/  dtrace_byfunc ; 
 int /*<<< orphan*/  dtrace_bymod ; 
 int /*<<< orphan*/  dtrace_byname ; 
 int /*<<< orphan*/  dtrace_byprov ; 
 int /*<<< orphan*/ * dtrace_devi ; 
 scalar_t__ dtrace_enable_nullop ; 
 TYPE_4__* dtrace_hash_lookup (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_hash_remove (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 scalar_t__ dtrace_opens ; 
 int /*<<< orphan*/  dtrace_probe_t_zone ; 
 int /*<<< orphan*/ ** dtrace_probes ; 
 TYPE_3__* dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  dtrace_strunref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_lock ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_4__*) ; 

int
dtrace_unregister(dtrace_provider_id_t id)
{
	dtrace_provider_t *old = (dtrace_provider_t *)id;
	dtrace_provider_t *prev = NULL;
	int self = 0;
	dtrace_probe_t *probe, *first = NULL, *next = NULL;
	dtrace_probe_t template = {
		.dtpr_provider = old
	};

	if (old->dtpv_pops.dtps_enable ==
	    (int (*)(void *, dtrace_id_t, void *))dtrace_enable_nullop) {
		/*
		 * If DTrace itself is the provider, we're called with locks
		 * already held.
		 */
		ASSERT(old == dtrace_provider);
		ASSERT(dtrace_devi != NULL);
		LCK_MTX_ASSERT(&dtrace_provider_lock, LCK_MTX_ASSERT_OWNED);
		LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
		self = 1;

		if (dtrace_provider->dtpv_next != NULL) {
			/*
			 * There's another provider here; return failure.
			 */
			return (EBUSY);
		}
	} else {
		lck_mtx_lock(&dtrace_provider_lock);
		lck_mtx_lock(&mod_lock);
		lck_mtx_lock(&dtrace_lock);
	}

	/*
	 * If anyone has /dev/dtrace open, or if there are anonymous enabled
	 * probes, we refuse to let providers slither away, unless this
	 * provider has already been explicitly invalidated.
	 */
	if (!old->dtpv_defunct &&
	    (dtrace_opens || (dtrace_anon.dta_state != NULL &&
	    dtrace_anon.dta_state->dts_necbs > 0))) {
		if (!self) {
			lck_mtx_unlock(&dtrace_lock);
			lck_mtx_unlock(&mod_lock);
			lck_mtx_unlock(&dtrace_provider_lock);
		}
		return (EBUSY);
	}

	/*
	 * Attempt to destroy the probes associated with this provider.
	 */
	if (old->dtpv_ecb_count!=0) {
		/*
		 * We have at least one ECB; we can't remove this provider.
		 */
		if (!self) {
			lck_mtx_unlock(&dtrace_lock);
			lck_mtx_unlock(&mod_lock);
			lck_mtx_unlock(&dtrace_provider_lock);
		}
		return (EBUSY);
	}

	/*
	 * All of the probes for this provider are disabled; we can safely
	 * remove all of them from their hash chains and from the probe array.
	 */
	for (probe = dtrace_hash_lookup(dtrace_byprov, &template); probe != NULL;
	    probe = *(DTRACE_HASHNEXT(dtrace_byprov, probe))) {
		if (probe->dtpr_provider != old)
			continue;

		dtrace_probes[probe->dtpr_id - 1] = NULL;
		old->dtpv_probe_count--;

		dtrace_hash_remove(dtrace_bymod, probe);
		dtrace_hash_remove(dtrace_byfunc, probe);
		dtrace_hash_remove(dtrace_byname, probe);

		if (first == NULL) {
			first = probe;
			probe->dtpr_nextmod = NULL;
		} else {
			/*
			 * Use nextmod as the chain of probes to remove
			 */
			probe->dtpr_nextmod = first;
			first = probe;
		}
	}

	for (probe = first; probe != NULL; probe = next) {
		next = probe->dtpr_nextmod;
		dtrace_hash_remove(dtrace_byprov, probe);
	}

	/*
	 * The provider's probes have been removed from the hash chains and
	 * from the probe array.  Now issue a dtrace_sync() to be sure that
	 * everyone has cleared out from any probe array processing.
	 */
	dtrace_sync();

	for (probe = first; probe != NULL; probe = next) {
		next = probe->dtpr_nextmod;

		old->dtpv_pops.dtps_destroy(old->dtpv_arg, probe->dtpr_id,
		    probe->dtpr_arg);
		dtrace_strunref(probe->dtpr_mod);
		dtrace_strunref(probe->dtpr_func);
		dtrace_strunref(probe->dtpr_name);
		vmem_free(dtrace_arena, (void *)(uintptr_t)(probe->dtpr_id), 1);
		zfree(dtrace_probe_t_zone, probe);
	}

	if ((prev = dtrace_provider) == old) {
		ASSERT(self || dtrace_devi == NULL);
		ASSERT(old->dtpv_next == NULL || dtrace_devi == NULL);
		dtrace_provider = old->dtpv_next;
	} else {
		while (prev != NULL && prev->dtpv_next != old)
			prev = prev->dtpv_next;

		if (prev == NULL) {
			panic("attempt to unregister non-existent "
			    "dtrace provider %p\n", (void *)id);
		}

		prev->dtpv_next = old->dtpv_next;
	}

	dtrace_strunref(old->dtpv_name);

	if (!self) {
		lck_mtx_unlock(&dtrace_lock);
		lck_mtx_unlock(&mod_lock);
		lck_mtx_unlock(&dtrace_provider_lock);
	}

	kmem_free(old, sizeof (dtrace_provider_t));

	return (0);
}