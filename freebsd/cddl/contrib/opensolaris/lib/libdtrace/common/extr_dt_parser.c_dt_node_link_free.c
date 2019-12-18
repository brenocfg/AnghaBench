#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* dn_link; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_node_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
dt_node_link_free(dt_node_t **pnp)
{
	dt_node_t *dnp, *nnp;

	for (dnp = (pnp != NULL ? *pnp : NULL); dnp != NULL; dnp = nnp) {
		nnp = dnp->dn_link;
		dt_node_free(dnp);
	}

	for (dnp = (pnp != NULL ? *pnp : NULL); dnp != NULL; dnp = nnp) {
		nnp = dnp->dn_link;
		free(dnp);
	}

	if (pnp != NULL)
		*pnp = NULL;
}