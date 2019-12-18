#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_16__ {TYPE_1__* dtad_difo; int /*<<< orphan*/  dtad_kind; } ;
typedef  TYPE_2__ dtrace_actdesc_t ;
struct TYPE_17__ {int /*<<< orphan*/  dn_value; struct TYPE_17__* dn_list; struct TYPE_17__* dn_args; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_14__ {int /*<<< orphan*/  dtdt_size; int /*<<< orphan*/  dtdt_flags; } ;
struct TYPE_15__ {TYPE_10__ dtdo_rtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_TF_BYREF ; 
 int /*<<< orphan*/  DTRACEACT_TRACEMEM ; 
 int /*<<< orphan*/  DTRACEACT_TRACEMEM_DYNSIZE ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_TRACEMEM_ADDR ; 
 int /*<<< orphan*/  D_TRACEMEM_ARGS ; 
 int /*<<< orphan*/  D_TRACEMEM_DYNSIZE ; 
 int /*<<< orphan*/  D_TRACEMEM_SIZE ; 
 int /*<<< orphan*/  dnerror (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 void* dt_as (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_10__ dt_int_rtype ; 
 scalar_t__ dt_node_is_integer (TYPE_3__*) ; 
 scalar_t__ dt_node_is_pointer (TYPE_3__*) ; 
 scalar_t__ dt_node_is_posconst (TYPE_3__*) ; 
 int /*<<< orphan*/  dt_node_is_scalar (TYPE_3__*) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_3__*,char*,int) ; 
 TYPE_2__* dt_stmt_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yypcb ; 

__attribute__((used)) static void
dt_action_tracemem(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	dtrace_actdesc_t *ap = dt_stmt_action(dtp, sdp);

	dt_node_t *addr = dnp->dn_args;
	dt_node_t *max = dnp->dn_args->dn_list;
	dt_node_t *size;

	char n[DT_TYPE_NAMELEN];

	if (dt_node_is_integer(addr) == 0 && dt_node_is_pointer(addr) == 0) {
		dnerror(addr, D_TRACEMEM_ADDR,
		    "tracemem( ) argument #1 is incompatible with "
		    "prototype:\n\tprototype: pointer or integer\n"
		    "\t argument: %s\n",
		    dt_node_type_name(addr, n, sizeof (n)));
	}

	if (dt_node_is_posconst(max) == 0) {
		dnerror(max, D_TRACEMEM_SIZE, "tracemem( ) argument #2 must "
		    "be a non-zero positive integral constant expression\n");
	}

	if ((size = max->dn_list) != NULL) {
		if (size->dn_list != NULL) {
			dnerror(size, D_TRACEMEM_ARGS, "tracemem ( ) prototype "
			    "mismatch: expected at most 3 args\n");
		}

		if (!dt_node_is_scalar(size)) {
			dnerror(size, D_TRACEMEM_DYNSIZE, "tracemem ( ) "
			    "dynamic size (argument #3) must be of "
			    "scalar type\n");
		}

		dt_cg(yypcb, size);
		ap->dtad_difo = dt_as(yypcb);
		ap->dtad_difo->dtdo_rtype = dt_int_rtype;
		ap->dtad_kind = DTRACEACT_TRACEMEM_DYNSIZE;

		ap = dt_stmt_action(dtp, sdp);
	}

	dt_cg(yypcb, addr);
	ap->dtad_difo = dt_as(yypcb);
	ap->dtad_kind = DTRACEACT_TRACEMEM;

	ap->dtad_difo->dtdo_rtype.dtdt_flags |= DIF_TF_BYREF;
	ap->dtad_difo->dtdo_rtype.dtdt_size = max->dn_value;
}