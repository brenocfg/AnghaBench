#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdesc_t ;
struct TYPE_6__ {int ii_nargs; struct TYPE_6__* ii_args; int /*<<< orphan*/ * ii_owner; int /*<<< orphan*/ * ii_name; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 void* xmalloc (int) ; 
 int /*<<< orphan*/ * xstrdup (int /*<<< orphan*/ *) ; 

iidesc_t *
iidesc_dup(iidesc_t *src)
{
	iidesc_t *tgt;

	tgt = xmalloc(sizeof (iidesc_t));
	bcopy(src, tgt, sizeof (iidesc_t));

	tgt->ii_name = src->ii_name ? xstrdup(src->ii_name) : NULL;
	tgt->ii_owner = src->ii_owner ? xstrdup(src->ii_owner) : NULL;

	if (tgt->ii_nargs) {
		tgt->ii_args = xmalloc(sizeof (tdesc_t *) * tgt->ii_nargs);
		bcopy(src->ii_args, tgt->ii_args,
		    sizeof (tdesc_t *) * tgt->ii_nargs);
	}

	return (tgt);
}