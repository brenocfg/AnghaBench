#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n ;
struct TYPE_17__ {int /*<<< orphan*/  dtsd_fmtdata; } ;
typedef  TYPE_1__ dtrace_stmtdesc_t ;
struct TYPE_18__ {scalar_t__ dt_gen; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_actdesc_t ;
struct TYPE_19__ {int dn_kind; char* dn_string; struct TYPE_19__* dn_list; TYPE_5__* dn_ident; int /*<<< orphan*/  dn_line; struct TYPE_19__* dn_args; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_20__ {int /*<<< orphan*/  dis_args; } ;
typedef  TYPE_4__ dt_idsig_t ;
struct TYPE_21__ {scalar_t__ di_gen; int di_flags; int /*<<< orphan*/  di_id; scalar_t__ di_data; int /*<<< orphan*/  di_name; struct TYPE_21__* di_iarg; } ;
typedef  TYPE_5__ dt_ident_t ;
struct TYPE_22__ {int /*<<< orphan*/  pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_PRINTA ; 
 int DT_IDFLG_MOD ; 
#define  DT_NODE_AGG 129 
#define  DT_NODE_STRING 128 
 int /*<<< orphan*/  DT_PRINTF_AGGREGATION ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_PRINTA_AGGARG ; 
 int /*<<< orphan*/  D_PRINTA_AGGBAD ; 
 int /*<<< orphan*/  D_PRINTA_PROTO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnerror (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dt_action_difconst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dt_printa_validate (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_printf_create (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dt_printf_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_stmt_action (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  yylineno ; 
 TYPE_6__* yypcb ; 

__attribute__((used)) static void
dt_action_printa(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	dt_ident_t *aid, *fid;
	dtrace_actdesc_t *ap;
	const char *format;
	dt_node_t *anp, *proto = NULL;

	char n[DT_TYPE_NAMELEN];
	int argc = 0, argr = 0;

	for (anp = dnp->dn_args; anp != NULL; anp = anp->dn_list)
		argc++; /* count up arguments for error messages below */

	switch (dnp->dn_args->dn_kind) {
	case DT_NODE_STRING:
		format = dnp->dn_args->dn_string;
		anp = dnp->dn_args->dn_list;
		argr = 2;
		break;
	case DT_NODE_AGG:
		format = NULL;
		anp = dnp->dn_args;
		argr = 1;
		break;
	default:
		format = NULL;
		anp = dnp->dn_args;
		argr = 1;
	}

	if (argc < argr) {
		dnerror(dnp, D_PRINTA_PROTO,
		    "%s( ) prototype mismatch: %d args passed, %d expected\n",
		    dnp->dn_ident->di_name, argc, argr);
	}

	assert(anp != NULL);

	while (anp != NULL) {
		if (anp->dn_kind != DT_NODE_AGG) {
			dnerror(dnp, D_PRINTA_AGGARG,
			    "%s( ) argument #%d is incompatible with "
			    "prototype:\n\tprototype: aggregation\n"
			    "\t argument: %s\n", dnp->dn_ident->di_name, argr,
			    dt_node_type_name(anp, n, sizeof (n)));
		}

		aid = anp->dn_ident;
		fid = aid->di_iarg;

		if (aid->di_gen == dtp->dt_gen &&
		    !(aid->di_flags & DT_IDFLG_MOD)) {
			dnerror(dnp, D_PRINTA_AGGBAD,
			    "undefined aggregation: @%s\n", aid->di_name);
		}

		/*
		 * If we have multiple aggregations, we must be sure that
		 * their key signatures match.
		 */
		if (proto != NULL) {
			dt_printa_validate(proto, anp);
		} else {
			proto = anp;
		}

		if (format != NULL) {
			yylineno = dnp->dn_line;

			sdp->dtsd_fmtdata =
			    dt_printf_create(yypcb->pcb_hdl, format);
			dt_printf_validate(sdp->dtsd_fmtdata,
			    DT_PRINTF_AGGREGATION, dnp->dn_ident, 1,
			    fid->di_id, ((dt_idsig_t *)aid->di_data)->dis_args);
			format = NULL;
		}

		ap = dt_stmt_action(dtp, sdp);
		dt_action_difconst(ap, anp->dn_ident->di_id, DTRACEACT_PRINTA);

		anp = anp->dn_list;
		argr++;
	}
}