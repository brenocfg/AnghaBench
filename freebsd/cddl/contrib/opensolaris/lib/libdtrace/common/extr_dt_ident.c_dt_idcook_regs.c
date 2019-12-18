#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  dtt_type; int /*<<< orphan*/  dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_11__ {scalar_t__ dn_kind; int dn_flags; scalar_t__ dn_value; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; } ;
typedef  TYPE_2__ dt_node_t ;
struct TYPE_12__ {int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_3__ dt_ident_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int DT_NF_SIGNED ; 
 scalar_t__ DT_NODE_INT ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_PROTO_ARG ; 
 int /*<<< orphan*/  D_PROTO_LEN ; 
 int /*<<< orphan*/  D_REGS_IDX ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dt_type_lookup (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dtrace_errmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_4__* yypcb ; 

__attribute__((used)) static void
dt_idcook_regs(dt_node_t *dnp, dt_ident_t *idp, int argc, dt_node_t *ap)
{
	dtrace_typeinfo_t dtt;
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	char n[DT_TYPE_NAMELEN];

	if (argc != 1) {
		xyerror(D_PROTO_LEN, "%s[ ] prototype mismatch: %d arg%s"
		    "passed, 1 expected\n", idp->di_name,
		    argc, argc == 1 ? " " : "s ");
	}

	if (ap->dn_kind != DT_NODE_INT) {
		xyerror(D_PROTO_ARG, "%s[ ] argument #1 is incompatible with "
		    "prototype:\n\tprototype: %s\n\t argument: %s\n",
		    idp->di_name, "integer constant",
		    dt_type_name(ap->dn_ctfp, ap->dn_type, n, sizeof (n)));
	}

	if ((ap->dn_flags & DT_NF_SIGNED) && (int64_t)ap->dn_value < 0) {
		xyerror(D_REGS_IDX, "index %lld is out of range for array %s\n",
		    (longlong_t)ap->dn_value, idp->di_name);
	}

	if (dt_type_lookup("uint64_t", &dtt) == -1) {
		xyerror(D_UNKNOWN, "failed to resolve type of %s: %s\n",
		    idp->di_name, dtrace_errmsg(dtp, dtrace_errno(dtp)));
	}

	idp->di_ctfp = dtt.dtt_ctfp;
	idp->di_type = dtt.dtt_type;

	dt_node_type_assign(dnp, idp->di_ctfp, idp->di_type, B_FALSE);
}