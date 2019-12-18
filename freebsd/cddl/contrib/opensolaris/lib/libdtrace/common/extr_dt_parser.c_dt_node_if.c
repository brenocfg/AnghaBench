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
struct TYPE_7__ {struct TYPE_7__* dn_alternate_body; struct TYPE_7__* dn_body; struct TYPE_7__* dn_conditional; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NODE_IF ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 

dt_node_t *
dt_node_if(dt_node_t *pred, dt_node_t *acts, dt_node_t *else_acts)
{
	dt_node_t *dnp = dt_node_alloc(DT_NODE_IF);
	dnp->dn_conditional = pred;
	dnp->dn_body = acts;
	dnp->dn_alternate_body = else_acts;

	return (dnp);
}