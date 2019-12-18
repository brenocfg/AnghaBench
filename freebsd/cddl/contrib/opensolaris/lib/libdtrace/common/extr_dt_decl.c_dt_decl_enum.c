#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_13__ {int /*<<< orphan*/  dd_type; int /*<<< orphan*/ * dd_ctfp; } ;
typedef  TYPE_5__ dt_decl_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_12__ {int /*<<< orphan*/ * ds_next; } ;
struct TYPE_14__ {scalar_t__ pcb_idepth; TYPE_4__ pcb_dstack; TYPE_3__* pcb_hdl; } ;
struct TYPE_11__ {TYPE_2__* dt_ddefs; TYPE_1__* dt_cdefs; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dm_ctfp; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dm_ctfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ADD_NONROOT ; 
 int /*<<< orphan*/  CTF_ADD_ROOT ; 
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  CTF_K_ENUM ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_DECL_TYPERED ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  ctf_add_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ctf_enum_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_lookup_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dt_decl_hasmembers ; 
 TYPE_5__* dt_decl_spec (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dt_scope_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_6__* yypcb ; 

dt_decl_t *
dt_decl_enum(char *name)
{
	dt_decl_t *ddp = dt_decl_spec(CTF_K_ENUM, name);
	char n[DT_TYPE_NAMELEN];
	ctf_file_t *ctfp;
	ctf_id_t type;
	uint_t flag;

	if (yypcb->pcb_idepth != 0)
		ctfp = yypcb->pcb_hdl->dt_cdefs->dm_ctfp;
	else
		ctfp = yypcb->pcb_hdl->dt_ddefs->dm_ctfp;

	if (yypcb->pcb_dstack.ds_next != NULL)
		flag = CTF_ADD_NONROOT;
	else
		flag = CTF_ADD_ROOT;

	(void) snprintf(n, sizeof (n), "enum %s", name ? name : "(anon)");

	if (name != NULL && (type = ctf_lookup_by_name(ctfp, n)) != CTF_ERR) {
		if (ctf_enum_iter(ctfp, type, dt_decl_hasmembers, NULL))
			xyerror(D_DECL_TYPERED, "type redeclared: %s\n", n);
	} else if ((type = ctf_add_enum(ctfp, flag, name)) == CTF_ERR) {
		xyerror(D_UNKNOWN, "failed to define %s: %s\n",
		    n, ctf_errmsg(ctf_errno(ctfp)));
	}

	ddp->dd_ctfp = ctfp;
	ddp->dd_type = type;

	dt_scope_push(ctfp, type);
	return (ddp);
}