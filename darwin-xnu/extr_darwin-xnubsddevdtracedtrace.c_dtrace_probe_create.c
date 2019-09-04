#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dtpv_probe_count; } ;
typedef  TYPE_1__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_13__ {int dtpr_id; int dtpr_aframes; TYPE_1__* dtpr_provider; void* dtpr_arg; void* dtpr_name; void* dtpr_func; void* dtpr_mod; scalar_t__ dtpr_gen; } ;
typedef  TYPE_2__ dtrace_probe_t ;
typedef  int dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int VM_BESTFIT ; 
 int VM_SLEEP ; 
 int /*<<< orphan*/  bcopy (TYPE_2__**,TYPE_2__**,size_t) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/  dtrace_byfunc ; 
 int /*<<< orphan*/  dtrace_bymod ; 
 int /*<<< orphan*/  dtrace_byname ; 
 int /*<<< orphan*/  dtrace_byprov ; 
 int /*<<< orphan*/  dtrace_hash_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_membar_producer () ; 
 int dtrace_nprobes ; 
 int /*<<< orphan*/  dtrace_probe_t_zone ; 
 int /*<<< orphan*/  dtrace_probegen ; 
 TYPE_2__** dtrace_probes ; 
 TYPE_1__* dtrace_provider ; 
 void* dtrace_strref (char const*) ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__**,size_t) ; 
 TYPE_2__** kmem_zalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* zalloc (int /*<<< orphan*/ ) ; 

dtrace_id_t
dtrace_probe_create(dtrace_provider_id_t prov, const char *mod,
    const char *func, const char *name, int aframes, void *arg)
{
	dtrace_probe_t *probe, **probes;
	dtrace_provider_t *provider = (dtrace_provider_t *)prov;
	dtrace_id_t id;

	if (provider == dtrace_provider) {
		LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
	} else {
		lck_mtx_lock(&dtrace_lock);
	}

	id = (dtrace_id_t)(uintptr_t)vmem_alloc(dtrace_arena, 1,
	    VM_BESTFIT | VM_SLEEP);

	probe = zalloc(dtrace_probe_t_zone);
	bzero(probe, sizeof (dtrace_probe_t));

	probe->dtpr_id = id;
	probe->dtpr_gen = dtrace_probegen++;
	probe->dtpr_mod = dtrace_strref(mod);
	probe->dtpr_func = dtrace_strref(func);
	probe->dtpr_name = dtrace_strref(name);
	probe->dtpr_arg = arg;
	probe->dtpr_aframes = aframes;
	probe->dtpr_provider = provider;

	dtrace_hash_add(dtrace_byprov, probe);
	dtrace_hash_add(dtrace_bymod, probe);
	dtrace_hash_add(dtrace_byfunc, probe);
	dtrace_hash_add(dtrace_byname, probe);

	if (id - 1 >= (dtrace_id_t)dtrace_nprobes) {
		size_t osize = dtrace_nprobes * sizeof (dtrace_probe_t *);
		size_t nsize = osize << 1;

		if (nsize == 0) {
			ASSERT(osize == 0);
			ASSERT(dtrace_probes == NULL);
			nsize = sizeof (dtrace_probe_t *);
		}

		probes = kmem_zalloc(nsize, KM_SLEEP);

		if (dtrace_probes == NULL) {
			ASSERT(osize == 0);
			dtrace_probes = probes;
			dtrace_nprobes = 1;
		} else {
			dtrace_probe_t **oprobes = dtrace_probes;

			bcopy(oprobes, probes, osize);
			dtrace_membar_producer();
			dtrace_probes = probes;

			dtrace_sync();

			/*
			 * All CPUs are now seeing the new probes array; we can
			 * safely free the old array.
			 */
			kmem_free(oprobes, osize);
			dtrace_nprobes <<= 1;
		}

		ASSERT(id - 1 < (dtrace_id_t)dtrace_nprobes);
	}

	ASSERT(dtrace_probes[id - 1] == NULL);
	dtrace_probes[id - 1] = probe;
	provider->dtpv_probe_count++;	

	if (provider != dtrace_provider)
		lck_mtx_unlock(&dtrace_lock);

	return (id);
}