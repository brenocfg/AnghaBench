#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_10__ {int /*<<< orphan*/  dt_xlators; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_11__ {size_t dx_nmembers; struct TYPE_11__* dx_membdif; int /*<<< orphan*/ * dx_ident; int /*<<< orphan*/ * dx_locals; int /*<<< orphan*/  dx_nodes; } ;
typedef  TYPE_2__ dt_xlator_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_difo_free (TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  dt_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_ident_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_idhash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_list_delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_node_link_free (int /*<<< orphan*/ *) ; 

void
dt_xlator_destroy(dtrace_hdl_t *dtp, dt_xlator_t *dxp)
{
	uint_t i;

	dt_node_link_free(&dxp->dx_nodes);

	if (dxp->dx_locals != NULL)
		dt_idhash_destroy(dxp->dx_locals);
	else if (dxp->dx_ident != NULL)
		dt_ident_destroy(dxp->dx_ident);

	for (i = 0; i < dxp->dx_nmembers; i++)
		dt_difo_free(dtp, dxp->dx_membdif[i]);

	dt_free(dtp, dxp->dx_membdif);
	dt_list_delete(&dtp->dt_xlators, dxp);
	dt_free(dtp, dxp);
}