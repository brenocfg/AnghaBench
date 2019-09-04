#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_11__ {int /*<<< orphan*/ * dtms_remove_proc; int /*<<< orphan*/ * dtms_provide_proc; int /*<<< orphan*/ * dtms_create_probe; } ;
typedef  TYPE_2__ dtrace_mops_t ;
struct TYPE_12__ {int /*<<< orphan*/  dtm_name; void* dtm_arg; TYPE_2__ dtm_mops; } ;
typedef  TYPE_3__ dtrace_meta_t ;
typedef  scalar_t__ dtrace_meta_provider_id_t ;
struct TYPE_13__ {size_t dthps_nprovs; scalar_t__ dthps_deferred; int /*<<< orphan*/ * dthps_prev; struct TYPE_13__* dthps_next; TYPE_1__** dthps_provs; int /*<<< orphan*/  dthps_pid; } ;
typedef  TYPE_4__ dtrace_helpers_t ;
struct TYPE_10__ {int /*<<< orphan*/  dthp_prov; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_WARN ; 
 scalar_t__ DTRACE_METAPROVNONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/ * PROC_NULL ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* dtrace_deferred_pid ; 
 int /*<<< orphan*/  dtrace_helper_provide (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 TYPE_3__* dtrace_meta_pid ; 
 int /*<<< orphan*/  dtrace_strref (char const*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 TYPE_3__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (int /*<<< orphan*/ *) ; 

int
dtrace_meta_register(const char *name, const dtrace_mops_t *mops, void *arg,
    dtrace_meta_provider_id_t *idp)
{
	dtrace_meta_t *meta;
	dtrace_helpers_t *help, *next;
	uint_t i;

	*idp = DTRACE_METAPROVNONE;

	/*
	 * We strictly don't need the name, but we hold onto it for
	 * debuggability. All hail error queues!
	 */
	if (name == NULL) {
		cmn_err(CE_WARN, "failed to register meta-provider: "
		    "invalid name");
		return (EINVAL);
	}

	if (mops == NULL ||
	    mops->dtms_create_probe == NULL ||
	    mops->dtms_provide_proc == NULL ||
	    mops->dtms_remove_proc == NULL) {
		cmn_err(CE_WARN, "failed to register meta-register %s: "
		    "invalid ops", name);
		return (EINVAL);
	}

	meta = kmem_zalloc(sizeof (dtrace_meta_t), KM_SLEEP);
	meta->dtm_mops = *mops;
	meta->dtm_arg = arg;

	lck_mtx_lock(&dtrace_meta_lock);
	lck_mtx_lock(&dtrace_lock);

	if (dtrace_meta_pid != NULL) {
		lck_mtx_unlock(&dtrace_lock);
		lck_mtx_unlock(&dtrace_meta_lock);
		cmn_err(CE_WARN, "failed to register meta-register %s: "
		    "user-land meta-provider exists", name);
		kmem_free(meta, sizeof (dtrace_meta_t));
		return (EINVAL);
	}

	meta->dtm_name = dtrace_strref(name);

	dtrace_meta_pid = meta;
	*idp = (dtrace_meta_provider_id_t)meta;

	/*
	 * If there are providers and probes ready to go, pass them
	 * off to the new meta provider now.
	 */

	help = dtrace_deferred_pid;
	dtrace_deferred_pid = NULL;

	lck_mtx_unlock(&dtrace_lock);

	while (help != NULL) {
		for (i = 0; i < help->dthps_nprovs; i++) {
			proc_t *p = proc_find(help->dthps_pid);
			if (p == PROC_NULL)
				continue;
			dtrace_helper_provide(&help->dthps_provs[i]->dthp_prov,
			    p);
			proc_rele(p);
		}

		next = help->dthps_next;
		help->dthps_next = NULL;
		help->dthps_prev = NULL;
		help->dthps_deferred = 0;
		help = next;
	}

	lck_mtx_unlock(&dtrace_meta_lock);

	return (0);
}