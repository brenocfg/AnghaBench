#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_9__ {size_t dt_modbuckets; scalar_t__ dt_nmods; int /*<<< orphan*/  dt_modlist; TYPE_2__** dt_mods; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_10__ {struct TYPE_10__* dm_next; int /*<<< orphan*/  dm_name; } ;
typedef  TYPE_2__ dt_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_list_delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_module_unload (TYPE_1__*,TYPE_2__*) ; 
 size_t dt_strtab_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void
dt_module_destroy(dtrace_hdl_t *dtp, dt_module_t *dmp)
{
	uint_t h = dt_strtab_hash(dmp->dm_name, NULL) % dtp->dt_modbuckets;
	dt_module_t **dmpp = &dtp->dt_mods[h];

	dt_list_delete(&dtp->dt_modlist, dmp);
	assert(dtp->dt_nmods != 0);
	dtp->dt_nmods--;

	/*
	 * Now remove this module from its hash chain.  We expect to always
	 * find the module on its hash chain, so in this loop we assert that
	 * we don't run off the end of the list.
	 */
	while (*dmpp != dmp) {
		dmpp = &((*dmpp)->dm_next);
		assert(*dmpp != NULL);
	}

	*dmpp = dmp->dm_next;

	dt_module_unload(dtp, dmp);
	free(dmp);
}