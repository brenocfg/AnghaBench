#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_4__ {size_t ds_symid; int /*<<< orphan*/  ds_next; } ;
typedef  TYPE_1__ dt_sym_t ;
struct TYPE_5__ {size_t dm_symfree; int dm_nsymelems; size_t dm_nsymbuckets; int /*<<< orphan*/ * dm_symbuckets; TYPE_1__* dm_symchains; } ;
typedef  TYPE_2__ dt_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t dt_strtab_hash (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_module_symhash_insert(dt_module_t *dmp, const char *name, uint_t id)
{
	dt_sym_t *dsp = &dmp->dm_symchains[dmp->dm_symfree];
	uint_t h;

	assert(dmp->dm_symfree < dmp->dm_nsymelems + 1);

	dsp->ds_symid = id;
	h = dt_strtab_hash(name, NULL) % dmp->dm_nsymbuckets;
	dsp->ds_next = dmp->dm_symbuckets[h];
	dmp->dm_symbuckets[h] = dmp->dm_symfree++;
}