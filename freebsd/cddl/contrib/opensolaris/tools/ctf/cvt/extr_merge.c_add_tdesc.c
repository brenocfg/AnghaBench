#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int t_id; size_t t_type; } ;
typedef  TYPE_3__ tdesc_t ;
struct TYPE_16__ {TYPE_2__* md_tgt; TYPE_1__* md_parent; } ;
typedef  TYPE_4__ merge_cb_data_t ;
struct TYPE_17__ {TYPE_3__* (* conjure ) (TYPE_3__*,int,TYPE_4__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  td_layouthash; int /*<<< orphan*/  td_idhash; } ;
struct TYPE_13__ {int /*<<< orphan*/  td_idhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_3__* stub1 (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  tdesc_name (TYPE_3__*) ; 
 TYPE_5__* tdesc_ops ; 

__attribute__((used)) static int
add_tdesc(tdesc_t *oldtdp, int newid, merge_cb_data_t *mcd)
{
	tdesc_t *newtdp;
	tdesc_t template;

	template.t_id = newid;
	assert(hash_find(mcd->md_parent->td_idhash,
	    (void *)&template, NULL) == 0);

	debug(3, "trying to conjure %d %s (%d, <%x>) as %d, <%x>\n",
	    oldtdp->t_type, tdesc_name(oldtdp), oldtdp->t_id,
	    oldtdp->t_id, newid, newid);

	if ((newtdp = tdesc_ops[oldtdp->t_type].conjure(oldtdp, newid,
	    mcd)) == NULL)
		/* couldn't map everything */
		return (0);

	debug(3, "succeeded\n");

	hash_add(mcd->md_tgt->td_idhash, newtdp);
	hash_add(mcd->md_tgt->td_layouthash, newtdp);

	return (1);
}