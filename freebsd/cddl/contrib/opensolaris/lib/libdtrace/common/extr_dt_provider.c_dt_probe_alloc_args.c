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
struct TYPE_6__ {TYPE_2__* pv_nodes; int /*<<< orphan*/  pv_hdl; } ;
typedef  TYPE_1__ dt_provider_t ;
struct TYPE_7__ {struct TYPE_7__* dn_list; struct TYPE_7__* dn_link; } ;
typedef  TYPE_2__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NODE_TYPE ; 
 TYPE_2__* dt_node_xalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dt_node_t *
dt_probe_alloc_args(dt_provider_t *pvp, int argc)
{
	dt_node_t *args = NULL, *pnp = NULL, *dnp;
	int i;

	for (i = 0; i < argc; i++, pnp = dnp) {
		if ((dnp = dt_node_xalloc(pvp->pv_hdl, DT_NODE_TYPE)) == NULL)
			return (NULL);

		dnp->dn_link = pvp->pv_nodes;
		pvp->pv_nodes = dnp;

		if (args == NULL)
			args = dnp;
		else
			pnp->dn_list = dnp;
	}

	return (args);
}