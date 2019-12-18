#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_predicate_t ;
typedef  int /*<<< orphan*/  dtrace_enabling_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dtpdd_predicate; } ;
struct TYPE_9__ {int /*<<< orphan*/  dted_uarg; int /*<<< orphan*/  dted_probe; TYPE_1__ dted_pred; TYPE_3__* dted_action; } ;
typedef  TYPE_2__ dtrace_ecbdesc_t ;
struct TYPE_10__ {struct TYPE_10__* dtad_next; } ;
typedef  TYPE_3__ dtrace_actdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  dtrace_actdesc_hold (TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_enabling_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dtrace_predicate_hold (int /*<<< orphan*/ *) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_enabling_addlike(dtrace_enabling_t *enab, dtrace_ecbdesc_t *ecb,
    dtrace_probedesc_t *pd)
{
	dtrace_ecbdesc_t *new;
	dtrace_predicate_t *pred;
	dtrace_actdesc_t *act;

	/*
	 * We're going to create a new ECB description that matches the
	 * specified ECB in every way, but has the specified probe description.
	 */
	new = kmem_zalloc(sizeof (dtrace_ecbdesc_t), KM_SLEEP);

	if ((pred = ecb->dted_pred.dtpdd_predicate) != NULL)
		dtrace_predicate_hold(pred);

	for (act = ecb->dted_action; act != NULL; act = act->dtad_next)
		dtrace_actdesc_hold(act);

	new->dted_action = ecb->dted_action;
	new->dted_pred = ecb->dted_pred;
	new->dted_probe = *pd;
	new->dted_uarg = ecb->dted_uarg;

	dtrace_enabling_add(enab, new);
}