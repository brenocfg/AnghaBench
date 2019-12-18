#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
struct TYPE_6__ {size_t dh_hashsz; scalar_t__ dh_nelems; TYPE_2__** dh_hash; } ;
typedef  TYPE_1__ dt_idhash_t ;
struct TYPE_7__ {int di_flags; struct TYPE_7__* di_next; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int DT_IDFLG_ORPHAN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_ident_destroy (TYPE_2__*) ; 
 size_t dt_strtab_hash (int /*<<< orphan*/ ,size_t*) ; 

void
dt_idhash_delete(dt_idhash_t *dhp, dt_ident_t *key)
{
	size_t len;
	ulong_t h = dt_strtab_hash(key->di_name, &len) % dhp->dh_hashsz;
	dt_ident_t **pp = &dhp->dh_hash[h];
	dt_ident_t *idp;

	for (idp = dhp->dh_hash[h]; idp != NULL; idp = idp->di_next) {
		if (idp == key)
			break;
		else
			pp = &idp->di_next;
	}

	assert(idp == key);
	*pp = idp->di_next;

	assert(dhp->dh_nelems != 0);
	dhp->dh_nelems--;

	if (!(idp->di_flags & DT_IDFLG_ORPHAN))
		dt_ident_destroy(idp);
}