#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * dtsd_strdata; } ;
typedef  TYPE_2__ dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_21__ {int /*<<< orphan*/  dtad_kind; int /*<<< orphan*/  dtad_difo; } ;
typedef  TYPE_3__ dtrace_actdesc_t ;
struct TYPE_22__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; TYPE_1__* dn_ident; TYPE_9__* dn_args; } ;
typedef  TYPE_4__ dt_node_t ;
struct TYPE_23__ {char* dm_name; scalar_t__ dm_pid; } ;
typedef  TYPE_5__ dt_module_t ;
typedef  int boolean_t ;
struct TYPE_25__ {scalar_t__ dn_kind; } ;
struct TYPE_24__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_4__* pcb_dret; } ;
struct TYPE_19__ {scalar_t__ di_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_DIFEXPR ; 
 scalar_t__ DT_ACT_PRINT ; 
 scalar_t__ DT_ACT_TRACE ; 
 int /*<<< orphan*/  DT_IDENT_XLPTR ; 
 scalar_t__ DT_NODE_AGG ; 
 int /*<<< orphan*/  D_PRINT_AGG ; 
 int /*<<< orphan*/  D_PRINT_DYN ; 
 int /*<<< orphan*/  D_PRINT_VOID ; 
 int /*<<< orphan*/  D_TRACE_AGG ; 
 int /*<<< orphan*/  D_TRACE_DYN ; 
 int /*<<< orphan*/  D_TRACE_VOID ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dnerror (TYPE_9__*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/ * dt_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dt_as (TYPE_6__*) ; 
 int /*<<< orphan*/  dt_cg (TYPE_6__*,TYPE_9__*) ; 
 int dt_module_getlibid (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* dt_module_lookup_by_ctf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_void (TYPE_9__*) ; 
 int /*<<< orphan*/ * dt_node_resolve (TYPE_9__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* dt_stmt_action (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (int /*<<< orphan*/ *,size_t,char*,char*,int,...) ; 
 TYPE_6__* yypcb ; 

__attribute__((used)) static void
dt_action_trace(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	int ctflib;

	dtrace_actdesc_t *ap = dt_stmt_action(dtp, sdp);
	boolean_t istrace = (dnp->dn_ident->di_id == DT_ACT_TRACE);
	const char *act = istrace ?  "trace" : "print";

	if (dt_node_is_void(dnp->dn_args)) {
		dnerror(dnp->dn_args, istrace ? D_TRACE_VOID : D_PRINT_VOID,
		    "%s( ) may not be applied to a void expression\n", act);
	}

	if (dt_node_resolve(dnp->dn_args, DT_IDENT_XLPTR) != NULL) {
		dnerror(dnp->dn_args, istrace ? D_TRACE_DYN : D_PRINT_DYN,
		    "%s( ) may not be applied to a translated pointer\n", act);
	}

	if (dnp->dn_args->dn_kind == DT_NODE_AGG) {
		dnerror(dnp->dn_args, istrace ? D_TRACE_AGG : D_PRINT_AGG,
		    "%s( ) may not be applied to an aggregation%s\n", act,
		    istrace ? "" : " -- did you mean printa()?");
	}

	dt_cg(yypcb, dnp->dn_args);

	/*
	 * The print() action behaves identically to trace(), except that it
	 * stores the CTF type of the argument (if present) within the DOF for
	 * the DIFEXPR action.  To do this, we set the 'dtsd_strdata' to point
	 * to the fully-qualified CTF type ID for the result of the DIF
	 * action.  We use the ID instead of the name to handles complex types
	 * like arrays and function pointers that can't be resolved by
	 * ctf_type_lookup().  This is later processed by dtrace_dof_create()
	 * and turned into a reference into the string table so that we can
	 * get the type information when we process the data after the fact.  In
	 * the case where we are referring to userland CTF data, we also need to
	 * to identify which ctf container in question we care about and encode
	 * that within the name.
	 */
	if (dnp->dn_ident->di_id == DT_ACT_PRINT) {
		dt_node_t *dret;
		size_t n;
		dt_module_t *dmp;

		dret = yypcb->pcb_dret;
		dmp = dt_module_lookup_by_ctf(dtp, dret->dn_ctfp);

		n = snprintf(NULL, 0, "%s`%ld", dmp->dm_name, dret->dn_type) + 1;
		if (dmp->dm_pid != 0) {
			ctflib = dt_module_getlibid(dtp, dmp, dret->dn_ctfp);
			assert(ctflib >= 0);
			n = snprintf(NULL, 0, "%s`%d`%ld", dmp->dm_name,
			    ctflib, dret->dn_type) + 1;
		} else {
			n = snprintf(NULL, 0, "%s`%ld", dmp->dm_name,
			    dret->dn_type) + 1;
		}
		sdp->dtsd_strdata = dt_alloc(dtp, n);
		if (sdp->dtsd_strdata == NULL)
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);
		(void) snprintf(sdp->dtsd_strdata, n, "%s`%ld", dmp->dm_name,
		    dret->dn_type);
		if (dmp->dm_pid != 0) {
			(void) snprintf(sdp->dtsd_strdata, n, "%s`%d`%ld",
			    dmp->dm_name, ctflib, dret->dn_type);
		} else {
			(void) snprintf(sdp->dtsd_strdata, n, "%s`%ld",
			    dmp->dm_name, dret->dn_type);
		}
	}

	ap->dtad_difo = dt_as(yypcb);
	ap->dtad_kind = DTRACEACT_DIFEXPR;
}