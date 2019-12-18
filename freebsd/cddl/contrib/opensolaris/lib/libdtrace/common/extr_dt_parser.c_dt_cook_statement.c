#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_7__ {TYPE_2__* dn_expr; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_8__ {int /*<<< orphan*/  dn_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dt_node_attr_assign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dt_node_cook (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dt_node_t *
dt_cook_statement(dt_node_t *dnp, uint_t idflags)
{
	dnp->dn_expr = dt_node_cook(dnp->dn_expr, idflags);
	dt_node_attr_assign(dnp, dnp->dn_expr->dn_attr);

	return (dnp);
}