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
struct TYPE_6__ {size_t dh_hashsz; TYPE_2__** dh_hash; int /*<<< orphan*/ * dh_tmpl; } ;
typedef  TYPE_1__ dt_idhash_t ;
struct TYPE_7__ {int /*<<< orphan*/  di_name; struct TYPE_7__* di_next; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_idhash_populate (TYPE_1__*) ; 
 size_t dt_strtab_hash (char const*,size_t*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

dt_ident_t *
dt_idhash_lookup(dt_idhash_t *dhp, const char *name)
{
	size_t len;
	ulong_t h = dt_strtab_hash(name, &len) % dhp->dh_hashsz;
	dt_ident_t *idp;

	if (dhp->dh_tmpl != NULL)
		dt_idhash_populate(dhp); /* fill hash w/ initial population */

	for (idp = dhp->dh_hash[h]; idp != NULL; idp = idp->di_next) {
		if (strcmp(idp->di_name, name) == 0)
			return (idp);
	}

	return (NULL);
}