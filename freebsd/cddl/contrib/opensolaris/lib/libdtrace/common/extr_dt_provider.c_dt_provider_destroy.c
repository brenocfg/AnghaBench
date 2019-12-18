#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_10__ {size_t dt_provbuckets; int /*<<< orphan*/  dt_nprovs; int /*<<< orphan*/  dt_provlist; TYPE_3__** dt_provs; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_9__ {int /*<<< orphan*/  dtvd_name; } ;
struct TYPE_11__ {struct TYPE_11__* pv_xrefs; int /*<<< orphan*/  pv_nodes; int /*<<< orphan*/ * pv_probes; struct TYPE_11__* pv_next; TYPE_1__ pv_desc; TYPE_2__* pv_hdl; } ;
typedef  TYPE_3__ dt_provider_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_free (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_idhash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_list_delete (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_node_link_free (int /*<<< orphan*/ *) ; 
 size_t dt_strtab_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dt_provider_destroy(dtrace_hdl_t *dtp, dt_provider_t *pvp)
{
	dt_provider_t **pp;
	uint_t h;

	assert(pvp->pv_hdl == dtp);

	h = dt_strtab_hash(pvp->pv_desc.dtvd_name, NULL) % dtp->dt_provbuckets;
	pp = &dtp->dt_provs[h];

	while (*pp != NULL && *pp != pvp)
		pp = &(*pp)->pv_next;

	assert(*pp != NULL && *pp == pvp);
	*pp = pvp->pv_next;

	dt_list_delete(&dtp->dt_provlist, pvp);
	dtp->dt_nprovs--;

	if (pvp->pv_probes != NULL)
		dt_idhash_destroy(pvp->pv_probes);

	dt_node_link_free(&pvp->pv_nodes);
	dt_free(dtp, pvp->pv_xrefs);
	dt_free(dtp, pvp);
}