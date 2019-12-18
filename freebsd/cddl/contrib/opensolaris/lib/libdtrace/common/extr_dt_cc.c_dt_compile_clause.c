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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {struct TYPE_5__* dn_list; struct TYPE_5__* dn_pdescs; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_compile_one_clause (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
dt_compile_clause(dtrace_hdl_t *dtp, dt_node_t *cnp)
{
	dt_node_t *pnp;

	for (pnp = cnp->dn_pdescs; pnp != NULL; pnp = pnp->dn_list)
		dt_compile_one_clause(dtp, cnp, pnp);
}