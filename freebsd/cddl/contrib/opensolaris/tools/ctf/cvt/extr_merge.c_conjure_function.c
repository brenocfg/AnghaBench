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
struct TYPE_9__ {TYPE_2__* t_fndef; int /*<<< orphan*/  t_id; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  merge_cb_data_t ;
struct TYPE_10__ {scalar_t__ fn_nargs; int /*<<< orphan*/ * fn_args; int /*<<< orphan*/  fn_vargs; int /*<<< orphan*/  fn_ret; } ;
typedef  TYPE_2__ fndef_t ;

/* Variables and functions */
 TYPE_1__* conjure_template (TYPE_1__*,int) ; 
 int /*<<< orphan*/  remap_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcalloc (int) ; 
 TYPE_2__* xmalloc (int) ; 

__attribute__((used)) static tdesc_t *
conjure_function(tdesc_t *old, int newselfid, merge_cb_data_t *mcd)
{
	tdesc_t *new = conjure_template(old, newselfid);
	fndef_t *nfn = xmalloc(sizeof (fndef_t));
	fndef_t *ofn = old->t_fndef;
	int i;

	(void) remap_node(&nfn->fn_ret, ofn->fn_ret, old->t_id, new, mcd);

	nfn->fn_nargs = ofn->fn_nargs;
	nfn->fn_vargs = ofn->fn_vargs;

	if (nfn->fn_nargs > 0)
		nfn->fn_args = xcalloc(sizeof (tdesc_t *) * ofn->fn_nargs);

	for (i = 0; i < (int) ofn->fn_nargs; i++) {
		(void) remap_node(&nfn->fn_args[i], ofn->fn_args[i], old->t_id,
		    new, mcd);
	}

	new->t_fndef = nfn;

	return (new);
}