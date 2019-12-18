#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  dtt_ctfp; int /*<<< orphan*/  dtt_type; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
struct TYPE_12__ {int dn_flags; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_decl_t ;
typedef  int /*<<< orphan*/  dn ;
struct TYPE_13__ {int ctm_offset; int /*<<< orphan*/  ctm_type; } ;
typedef  TYPE_3__ ctf_membinfo_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_14__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CTF_ERR ; 
 scalar_t__ CTF_K_STRUCT ; 
 scalar_t__ CTF_K_UNION ; 
 int DT_NF_BITFIELD ; 
 int /*<<< orphan*/  D_OFFSETOF_BITFIELD ; 
 int /*<<< orphan*/  D_OFFSETOF_TYPE ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  EDT_COMPILER ; 
 int NBBY ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ctf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_member_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_decl_free (int /*<<< orphan*/ *) ; 
 int dt_decl_type (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* dt_node_int (int) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* yypcb ; 

dt_node_t *
dt_node_offsetof(dt_decl_t *ddp, char *s)
{
	dtrace_typeinfo_t dtt;
	dt_node_t dn;
	char *name;
	int err;

	ctf_membinfo_t ctm;
	ctf_id_t type;
	uint_t kind;

	name = alloca(strlen(s) + 1);
	(void) strcpy(name, s);
	free(s);

	err = dt_decl_type(ddp, &dtt);
	dt_decl_free(ddp);

	if (err != 0)
		longjmp(yypcb->pcb_jmpbuf, EDT_COMPILER);

	type = ctf_type_resolve(dtt.dtt_ctfp, dtt.dtt_type);
	kind = ctf_type_kind(dtt.dtt_ctfp, type);

	if (kind != CTF_K_STRUCT && kind != CTF_K_UNION) {
		xyerror(D_OFFSETOF_TYPE,
		    "offsetof operand must be a struct or union type\n");
	}

	if (ctf_member_info(dtt.dtt_ctfp, type, name, &ctm) == CTF_ERR) {
		xyerror(D_UNKNOWN, "failed to determine offset of %s: %s\n",
		    name, ctf_errmsg(ctf_errno(dtt.dtt_ctfp)));
	}

	bzero(&dn, sizeof (dn));
	dt_node_type_assign(&dn, dtt.dtt_ctfp, ctm.ctm_type, B_FALSE);

	if (dn.dn_flags & DT_NF_BITFIELD) {
		xyerror(D_OFFSETOF_BITFIELD,
		    "cannot take offset of a bit-field: %s\n", name);
	}

	return (dt_node_int(ctm.ctm_offset / NBBY));
}