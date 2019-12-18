#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_9__ {TYPE_6__* dn_ident; int /*<<< orphan*/  dn_aggtup; int /*<<< orphan*/ * dn_aggfun; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  di_attr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DT_DYN_CTFP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DT_DYN_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DT_IDFLG_REF ; 
 int /*<<< orphan*/  dt_ident_cook (TYPE_1__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_attr_assign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_node_cook (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static dt_node_t *
dt_cook_aggregation(dt_node_t *dnp, uint_t idflags)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;

	if (dnp->dn_aggfun != NULL) {
		dnp->dn_aggfun = dt_node_cook(dnp->dn_aggfun, DT_IDFLG_REF);
		dt_node_attr_assign(dnp, dt_ident_cook(dnp,
		    dnp->dn_ident, &dnp->dn_aggtup));
	} else {
		dt_node_type_assign(dnp, DT_DYN_CTFP(dtp), DT_DYN_TYPE(dtp),
		    B_FALSE);
		dt_node_attr_assign(dnp, dnp->dn_ident->di_attr);
	}

	return (dnp);
}