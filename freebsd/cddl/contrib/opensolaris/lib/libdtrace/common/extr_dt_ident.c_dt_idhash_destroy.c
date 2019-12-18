#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
struct TYPE_8__ {size_t dh_hashsz; struct TYPE_8__* di_name; struct TYPE_8__* di_next; struct TYPE_8__** dh_hash; TYPE_1__* di_ops; } ;
typedef  TYPE_2__ dt_idhash_t ;
typedef  TYPE_2__ dt_ident_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* di_dtor ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
dt_idhash_destroy(dt_idhash_t *dhp)
{
	dt_ident_t *idp, *next;
	ulong_t i;

	for (i = 0; i < dhp->dh_hashsz; i++) {
		for (idp = dhp->dh_hash[i]; idp != NULL; idp = next) {
			next = idp->di_next;
			idp->di_ops->di_dtor(idp);
		}
	}

	for (i = 0; i < dhp->dh_hashsz; i++) {
		for (idp = dhp->dh_hash[i]; idp != NULL; idp = next) {
			next = idp->di_next;
			free(idp->di_name);
			free(idp);
		}
	}

	free(dhp);
}