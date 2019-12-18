#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* ds_decl; } ;
typedef  TYPE_1__ dt_scope_t ;
struct TYPE_14__ {scalar_t__ dn_kind; scalar_t__ dn_value; } ;
typedef  TYPE_2__ dt_node_t ;
struct TYPE_15__ {scalar_t__ dd_kind; TYPE_2__* dd_node; int /*<<< orphan*/ * dd_name; struct TYPE_15__* dd_next; } ;
typedef  TYPE_3__ dt_decl_t ;
struct TYPE_16__ {TYPE_1__ pcb_dstack; } ;

/* Variables and functions */
 scalar_t__ CTF_K_ARRAY ; 
 int /*<<< orphan*/  DT_DP_ANON ; 
 int /*<<< orphan*/  DT_IDFLG_REF ; 
 scalar_t__ DT_NODE_TYPE ; 
 int /*<<< orphan*/  D_DECL_ARRBIG ; 
 int /*<<< orphan*/  D_DECL_ARRSUB ; 
 int /*<<< orphan*/  D_DECL_DYNOBJ ; 
 int /*<<< orphan*/  D_DECL_VOIDOBJ ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  dt_decl_alloc (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_decl_prototype (TYPE_2__*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* dt_decl_push (int /*<<< orphan*/ ) ; 
 TYPE_2__* dt_node_cook (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_posconst (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* yypcb ; 

dt_decl_t *
dt_decl_array(dt_node_t *dnp)
{
	dt_decl_t *ddp = dt_decl_push(dt_decl_alloc(CTF_K_ARRAY, NULL));
	dt_scope_t *dsp = &yypcb->pcb_dstack;
	dt_decl_t *ndp = ddp;

	/*
	 * After pushing the array on to the decl stack, scan ahead for multi-
	 * dimensional array declarations and push the current decl to the
	 * bottom to match the resulting CTF type tree and data layout.  Refer
	 * to the comments in dt_decl_type() and ISO C 6.5.2.1 for more info.
	 */
	while (ndp->dd_next != NULL && ndp->dd_next->dd_kind == CTF_K_ARRAY)
		ndp = ndp->dd_next; /* skip to bottom-most array declaration */

	if (ndp != ddp) {
		if (dnp != NULL && dnp->dn_kind == DT_NODE_TYPE) {
			xyerror(D_DECL_DYNOBJ,
			    "cannot declare array of associative arrays\n");
		}
		dsp->ds_decl = ddp->dd_next;
		ddp->dd_next = ndp->dd_next;
		ndp->dd_next = ddp;
	}

	if (ddp->dd_next->dd_name != NULL &&
	    strcmp(ddp->dd_next->dd_name, "void") == 0)
		xyerror(D_DECL_VOIDOBJ, "cannot declare array of void\n");

	if (dnp != NULL && dnp->dn_kind != DT_NODE_TYPE) {
		dnp = ddp->dd_node = dt_node_cook(dnp, DT_IDFLG_REF);

		if (dt_node_is_posconst(dnp) == 0) {
			xyerror(D_DECL_ARRSUB, "positive integral constant "
			    "expression or tuple signature expected as "
			    "array declaration subscript\n");
		}

		if (dnp->dn_value > UINT_MAX)
			xyerror(D_DECL_ARRBIG, "array dimension too big\n");

	} else if (dnp != NULL) {
		ddp->dd_node = dnp;
		(void) dt_decl_prototype(dnp, dnp, "array", DT_DP_ANON);
	}

	return (ddp);
}