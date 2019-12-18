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
typedef  int /*<<< orphan*/  ushort_t ;
typedef  size_t ulong_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_attribute_t ;
typedef  int /*<<< orphan*/  dt_idops_t ;
struct TYPE_9__ {size_t dh_hashsz; int /*<<< orphan*/  (* dh_defer ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  dh_nelems; TYPE_2__** dh_hash; int /*<<< orphan*/ * dh_tmpl; } ;
typedef  TYPE_1__ dt_idhash_t ;
struct TYPE_10__ {struct TYPE_10__* di_next; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 TYPE_2__* dt_ident_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,size_t) ; 
 int /*<<< orphan*/  dt_idhash_populate (TYPE_1__*) ; 
 size_t dt_strtab_hash (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*) ; 

dt_ident_t *
dt_idhash_insert(dt_idhash_t *dhp, const char *name, ushort_t kind,
    ushort_t flags, uint_t id, dtrace_attribute_t attr, uint_t vers,
    const dt_idops_t *ops, void *iarg, ulong_t gen)
{
	dt_ident_t *idp;
	ulong_t h;

	if (dhp->dh_tmpl != NULL)
		dt_idhash_populate(dhp); /* fill hash w/ initial population */

	idp = dt_ident_create(name, kind, flags, id,
	    attr, vers, ops, iarg, gen);

	if (idp == NULL)
		return (NULL);

	h = dt_strtab_hash(name, NULL) % dhp->dh_hashsz;
	idp->di_next = dhp->dh_hash[h];

	dhp->dh_hash[h] = idp;
	dhp->dh_nelems++;

	if (dhp->dh_defer != NULL)
		dhp->dh_defer(dhp, idp);

	return (idp);
}