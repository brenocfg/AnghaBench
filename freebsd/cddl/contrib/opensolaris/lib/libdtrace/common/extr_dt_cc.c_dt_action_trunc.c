#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
struct TYPE_14__ {scalar_t__ dt_gen; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_15__ {void* dtad_arg; int /*<<< orphan*/  dtad_kind; int /*<<< orphan*/  dtad_difo; } ;
typedef  TYPE_2__ dtrace_actdesc_t ;
struct TYPE_16__ {scalar_t__ dn_kind; TYPE_4__* dn_ident; struct TYPE_16__* dn_list; struct TYPE_16__* dn_args; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_17__ {scalar_t__ di_gen; int di_flags; int /*<<< orphan*/  di_id; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_4__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_LIBACT ; 
 void* DT_ACT_TRUNC ; 
 int DT_IDFLG_MOD ; 
 scalar_t__ DT_NODE_AGG ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_TRUNC_AGGARG ; 
 int /*<<< orphan*/  D_TRUNC_AGGBAD ; 
 int /*<<< orphan*/  D_TRUNC_PROTO ; 
 int /*<<< orphan*/  D_TRUNC_SCALAR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnerror (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dt_action_difconst (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_as (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_node_is_scalar (TYPE_3__*) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_3__*,char*,int) ; 
 TYPE_2__* dt_stmt_action (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yypcb ; 

__attribute__((used)) static void
dt_action_trunc(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	dt_ident_t *aid;
	dtrace_actdesc_t *ap;
	dt_node_t *anp, *trunc;

	char n[DT_TYPE_NAMELEN];
	int argc = 0;

	for (anp = dnp->dn_args; anp != NULL; anp = anp->dn_list)
		argc++; /* count up arguments for error messages below */

	if (argc > 2 || argc < 1) {
		dnerror(dnp, D_TRUNC_PROTO,
		    "%s( ) prototype mismatch: %d args passed, %s expected\n",
		    dnp->dn_ident->di_name, argc,
		    argc < 1 ? "at least 1" : "no more than 2");
	}

	anp = dnp->dn_args;
	assert(anp != NULL);
	trunc = anp->dn_list;

	if (anp->dn_kind != DT_NODE_AGG) {
		dnerror(dnp, D_TRUNC_AGGARG,
		    "%s( ) argument #1 is incompatible with prototype:\n"
		    "\tprototype: aggregation\n\t argument: %s\n",
		    dnp->dn_ident->di_name,
		    dt_node_type_name(anp, n, sizeof (n)));
	}

	if (argc == 2) {
		assert(trunc != NULL);
		if (!dt_node_is_scalar(trunc)) {
			dnerror(dnp, D_TRUNC_SCALAR,
			    "%s( ) argument #2 must be of scalar type\n",
			    dnp->dn_ident->di_name);
		}
	}

	aid = anp->dn_ident;

	if (aid->di_gen == dtp->dt_gen && !(aid->di_flags & DT_IDFLG_MOD)) {
		dnerror(dnp, D_TRUNC_AGGBAD,
		    "undefined aggregation: @%s\n", aid->di_name);
	}

	ap = dt_stmt_action(dtp, sdp);
	dt_action_difconst(ap, anp->dn_ident->di_id, DTRACEACT_LIBACT);
	ap->dtad_arg = DT_ACT_TRUNC;

	ap = dt_stmt_action(dtp, sdp);

	if (argc == 1) {
		dt_action_difconst(ap, 0, DTRACEACT_LIBACT);
	} else {
		assert(trunc != NULL);
		dt_cg(yypcb, trunc);
		ap->dtad_difo = dt_as(yypcb);
		ap->dtad_kind = DTRACEACT_LIBACT;
	}

	ap->dtad_arg = DT_ACT_TRUNC;
}