#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* dtps_enable ) (void*,dtrace_id_t,void*) ;int /*<<< orphan*/  (* dtps_destroy ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  dtpv_arg; TYPE_1__ dtpv_pops; int /*<<< orphan*/  dtpv_probe_count; } ;
typedef  TYPE_2__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_12__ {int dtpr_id; struct TYPE_12__* dtpr_nextmod; int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; int /*<<< orphan*/  dtpr_arg; int /*<<< orphan*/ * dtpr_ecb; TYPE_2__* dtpr_provider; } ;
typedef  TYPE_3__ dtrace_probe_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__** DTRACE_HASHNEXT (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/  dtrace_byfunc ; 
 int /*<<< orphan*/  dtrace_bymod ; 
 int /*<<< orphan*/  dtrace_byname ; 
 int /*<<< orphan*/  dtrace_byprov ; 
 scalar_t__ dtrace_enable_nullop ; 
 TYPE_3__* dtrace_hash_lookup (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_hash_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_probe_t_zone ; 
 int /*<<< orphan*/ ** dtrace_probes ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  dtrace_strunref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_3__*) ; 

int
dtrace_condense(dtrace_provider_id_t id)
{
	dtrace_provider_t *prov = (dtrace_provider_t *)id;
	dtrace_probe_t *probe, *first = NULL;
	dtrace_probe_t template = {
		.dtpr_provider = prov
	};

	/*
	 * Make sure this isn't the dtrace provider itself.
	 */
	ASSERT(prov->dtpv_pops.dtps_enable !=
	  (int (*)(void *, dtrace_id_t, void *))dtrace_enable_nullop);

	lck_mtx_lock(&dtrace_provider_lock);
	lck_mtx_lock(&dtrace_lock);

	/*
	 * Attempt to destroy the probes associated with this provider.
	 */
	for (probe = dtrace_hash_lookup(dtrace_byprov, &template); probe != NULL;
	    probe = *(DTRACE_HASHNEXT(dtrace_byprov, probe))) {

		if (probe->dtpr_provider != prov)
			continue;

		if (probe->dtpr_ecb != NULL)
			continue;

		dtrace_probes[probe->dtpr_id - 1] = NULL;
		prov->dtpv_probe_count--;

		dtrace_hash_remove(dtrace_bymod, probe);
		dtrace_hash_remove(dtrace_byfunc, probe);
		dtrace_hash_remove(dtrace_byname, probe);

		prov->dtpv_pops.dtps_destroy(prov->dtpv_arg, probe->dtpr_id,
		    probe->dtpr_arg);
		dtrace_strunref(probe->dtpr_mod);
		dtrace_strunref(probe->dtpr_func);
		dtrace_strunref(probe->dtpr_name);
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

	for (probe = first; probe != NULL; probe = first) {
		first = probe->dtpr_nextmod;
		dtrace_hash_remove(dtrace_byprov, probe);
		vmem_free(dtrace_arena, (void *)((uintptr_t)probe->dtpr_id), 1);
		zfree(dtrace_probe_t_zone, probe);
	}

	lck_mtx_unlock(&dtrace_lock);
	lck_mtx_unlock(&dtrace_provider_lock);

	return (0);
}