#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  sn ;
typedef  int /*<<< orphan*/  n2 ;
typedef  int /*<<< orphan*/  n1 ;
struct TYPE_18__ {int /*<<< orphan*/  dtt_type; int /*<<< orphan*/  dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_xlator_t ;
struct TYPE_19__ {struct TYPE_19__* dn_members; int /*<<< orphan*/ * dn_xlator; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_decl_t ;
typedef  int /*<<< orphan*/  dn ;
struct TYPE_20__ {int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/  pcb_list; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CTF_K_FORWARD ; 
 scalar_t__ CTF_K_STRUCT ; 
 scalar_t__ CTF_K_UNION ; 
 int /*<<< orphan*/  DT_IDFLG_REF ; 
 int /*<<< orphan*/  DT_NODE_XLATOR ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  DT_XLATE_EXACT ; 
 int /*<<< orphan*/  D_XLATE_REDECL ; 
 int /*<<< orphan*/  D_XLATE_SOU ; 
 int /*<<< orphan*/  EDT_COMPILER ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  YYS_CLAUSE ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_decl_free (int /*<<< orphan*/ *) ; 
 int dt_decl_type (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 TYPE_2__* dt_node_cook (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dt_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * dt_xlator_create (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_xlator_lookup (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  yybegin (int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

dt_node_t *
dt_node_xlator(dt_decl_t *ddp, dt_decl_t *sdp, char *name, dt_node_t *members)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	dtrace_typeinfo_t src, dst;
	dt_node_t sn, dn;
	dt_xlator_t *dxp;
	dt_node_t *dnp;
	int edst, esrc;
	uint_t kind;

	char n1[DT_TYPE_NAMELEN];
	char n2[DT_TYPE_NAMELEN];

	edst = dt_decl_type(ddp, &dst);
	dt_decl_free(ddp);

	esrc = dt_decl_type(sdp, &src);
	dt_decl_free(sdp);

	if (edst != 0 || esrc != 0) {
		free(name);
		longjmp(yypcb->pcb_jmpbuf, EDT_COMPILER);
	}

	bzero(&sn, sizeof (sn));
	dt_node_type_assign(&sn, src.dtt_ctfp, src.dtt_type, B_FALSE);

	bzero(&dn, sizeof (dn));
	dt_node_type_assign(&dn, dst.dtt_ctfp, dst.dtt_type, B_FALSE);

	if (dt_xlator_lookup(dtp, &sn, &dn, DT_XLATE_EXACT) != NULL) {
		xyerror(D_XLATE_REDECL,
		    "translator from %s to %s has already been declared\n",
		    dt_node_type_name(&sn, n1, sizeof (n1)),
		    dt_node_type_name(&dn, n2, sizeof (n2)));
	}

	kind = ctf_type_kind(dst.dtt_ctfp,
	    ctf_type_resolve(dst.dtt_ctfp, dst.dtt_type));

	if (kind == CTF_K_FORWARD) {
		xyerror(D_XLATE_SOU, "incomplete struct/union/enum %s\n",
		    dt_type_name(dst.dtt_ctfp, dst.dtt_type, n1, sizeof (n1)));
	}

	if (kind != CTF_K_STRUCT && kind != CTF_K_UNION) {
		xyerror(D_XLATE_SOU,
		    "translator output type must be a struct or union\n");
	}

	dxp = dt_xlator_create(dtp, &src, &dst, name, members, yypcb->pcb_list);
	yybegin(YYS_CLAUSE);
	free(name);

	if (dxp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dnp = dt_node_alloc(DT_NODE_XLATOR);
	dnp->dn_xlator = dxp;
	dnp->dn_members = members;

	return (dt_node_cook(dnp, DT_IDFLG_REF));
}