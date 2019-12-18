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
struct TYPE_7__ {scalar_t__ dn_kind; struct TYPE_7__* dn_expr; TYPE_1__* dn_ident; } ;
typedef  TYPE_2__ dt_node_t ;
struct TYPE_6__ {scalar_t__ di_kind; } ;

/* Variables and functions */
 scalar_t__ DT_IDENT_ACTFUNC ; 
 scalar_t__ DT_NODE_AGG ; 
 int /*<<< orphan*/  DT_NODE_DEXPR ; 
 int /*<<< orphan*/  DT_NODE_DFUNC ; 
 scalar_t__ DT_NODE_FUNC ; 
 TYPE_2__* dt_node_alloc (int /*<<< orphan*/ ) ; 

dt_node_t *
dt_node_statement(dt_node_t *expr)
{
	dt_node_t *dnp;

	if (expr->dn_kind == DT_NODE_AGG)
		return (expr);

	if (expr->dn_kind == DT_NODE_FUNC &&
	    expr->dn_ident->di_kind == DT_IDENT_ACTFUNC)
		dnp = dt_node_alloc(DT_NODE_DFUNC);
	else
		dnp = dt_node_alloc(DT_NODE_DEXPR);

	dnp->dn_expr = expr;
	return (dnp);
}