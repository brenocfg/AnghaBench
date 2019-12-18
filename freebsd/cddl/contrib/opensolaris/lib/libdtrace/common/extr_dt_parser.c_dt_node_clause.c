#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* dn_acts; struct TYPE_7__* dn_pred; struct TYPE_7__* dn_pdescs; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NODE_CLAUSE ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 

dt_node_t *
dt_node_clause(dt_node_t *pdescs, dt_node_t *pred, dt_node_t *acts)
{
	dt_node_t *dnp = dt_node_alloc(DT_NODE_CLAUSE);

	dnp->dn_pdescs = pdescs;
	dnp->dn_pred = pred;
	dnp->dn_acts = acts;

	return (dnp);
}