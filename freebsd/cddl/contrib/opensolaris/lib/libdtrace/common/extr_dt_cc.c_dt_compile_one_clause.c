#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_19__ {int /*<<< orphan*/  dtpdd_difo; } ;
struct TYPE_20__ {TYPE_1__ dted_pred; } ;
typedef  TYPE_2__ dtrace_ecbdesc_t ;
struct TYPE_21__ {int dn_kind; struct TYPE_21__* dn_expr; int /*<<< orphan*/  dn_attr; int /*<<< orphan*/  dn_ctxattr; struct TYPE_21__* dn_list; struct TYPE_21__* dn_acts; int /*<<< orphan*/ * dn_pred; int /*<<< orphan*/  dn_desc; int /*<<< orphan*/  dn_line; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_22__ {TYPE_2__* pcb_ecbdesc; int /*<<< orphan*/ * pcb_stmt; int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_IDFLG_REF ; 
#define  DT_NODE_AGG 130 
#define  DT_NODE_DEXPR 129 
#define  DT_NODE_DFUNC 128 
 scalar_t__ DT_TREEDUMP_PASS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  _dtrace_defattr ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dnerror (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dt_as (TYPE_4__*) ; 
 int /*<<< orphan*/  dt_cg (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_compile_agg (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_compile_exp (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_compile_fun (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* dt_ecbdesc_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_ecbdesc_release (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_endcontext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_cook (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_printr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_setcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_stmt_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * dt_stmt_create (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  yylineno ; 
 TYPE_4__* yypcb ; 

__attribute__((used)) static void
dt_compile_one_clause(dtrace_hdl_t *dtp, dt_node_t *cnp, dt_node_t *pnp)
{
	dtrace_ecbdesc_t *edp;
	dtrace_stmtdesc_t *sdp;
	dt_node_t *dnp;

	yylineno = pnp->dn_line;
	dt_setcontext(dtp, pnp->dn_desc);
	(void) dt_node_cook(cnp, DT_IDFLG_REF);

	if (DT_TREEDUMP_PASS(dtp, 2))
		dt_node_printr(cnp, stderr, 0);

	if ((edp = dt_ecbdesc_create(dtp, pnp->dn_desc)) == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	assert(yypcb->pcb_ecbdesc == NULL);
	yypcb->pcb_ecbdesc = edp;

	if (cnp->dn_pred != NULL) {
		dt_cg(yypcb, cnp->dn_pred);
		edp->dted_pred.dtpdd_difo = dt_as(yypcb);
	}

	if (cnp->dn_acts == NULL) {
		dt_stmt_append(dt_stmt_create(dtp, edp,
		    cnp->dn_ctxattr, _dtrace_defattr), cnp);
	}

	for (dnp = cnp->dn_acts; dnp != NULL; dnp = dnp->dn_list) {
		assert(yypcb->pcb_stmt == NULL);
		sdp = dt_stmt_create(dtp, edp, cnp->dn_ctxattr, cnp->dn_attr);

		switch (dnp->dn_kind) {
		case DT_NODE_DEXPR:
			if (dnp->dn_expr->dn_kind == DT_NODE_AGG)
				dt_compile_agg(dtp, dnp->dn_expr, sdp);
			else
				dt_compile_exp(dtp, dnp, sdp);
			break;
		case DT_NODE_DFUNC:
			dt_compile_fun(dtp, dnp, sdp);
			break;
		case DT_NODE_AGG:
			dt_compile_agg(dtp, dnp, sdp);
			break;
		default:
			dnerror(dnp, D_UNKNOWN, "internal error -- node kind "
			    "%u is not a valid statement\n", dnp->dn_kind);
		}

		assert(yypcb->pcb_stmt == sdp);
		dt_stmt_append(sdp, dnp);
	}

	assert(yypcb->pcb_ecbdesc == edp);
	dt_ecbdesc_release(dtp, edp);
	dt_endcontext(dtp);
	yypcb->pcb_ecbdesc = NULL;
}