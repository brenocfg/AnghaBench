#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  long ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  dtdv_type; int /*<<< orphan*/  dtdv_flags; int /*<<< orphan*/  dtdv_scope; int /*<<< orphan*/  dtdv_kind; int /*<<< orphan*/  dtdv_id; scalar_t__ dtdv_name; } ;
typedef  TYPE_2__ dtrace_difv_t ;
struct TYPE_8__ {int /*<<< orphan*/  pcb_hdl; int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/  pcb_strtab; int /*<<< orphan*/  pcb_asvidx; TYPE_1__* pcb_difo; } ;
typedef  TYPE_3__ dt_pcb_t ;
typedef  int /*<<< orphan*/  dt_node_t ;
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_9__ {int di_flags; scalar_t__ di_kind; int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; int /*<<< orphan*/  di_id; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_4__ dt_ident_t ;
typedef  int /*<<< orphan*/  dn ;
struct TYPE_6__ {TYPE_2__* dtdo_vartab; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DIFV_F_MOD ; 
 int /*<<< orphan*/  DIFV_F_REF ; 
 int /*<<< orphan*/  DIFV_KIND_ARRAY ; 
 int /*<<< orphan*/  DIFV_KIND_SCALAR ; 
 int /*<<< orphan*/  DIFV_SCOPE_GLOBAL ; 
 int /*<<< orphan*/  DIFV_SCOPE_LOCAL ; 
 int /*<<< orphan*/  DIFV_SCOPE_THREAD ; 
 long DIF_STROFF_MAX ; 
 scalar_t__ DT_IDENT_ARRAY ; 
 int DT_IDFLG_DIFR ; 
 int DT_IDFLG_DIFW ; 
 int DT_IDFLG_LOCAL ; 
 int DT_IDFLG_TLS ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  EDT_STR2BIG ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dt_node_diftype (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_type_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long dt_strtab_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_copyvar(dt_idhash_t *dhp, dt_ident_t *idp, void *data)
{
	dt_pcb_t *pcb = data;
	dtrace_difv_t *dvp;
	ssize_t stroff;
	dt_node_t dn;

	if (!(idp->di_flags & (DT_IDFLG_DIFR | DT_IDFLG_DIFW)))
		return (0); /* omit variable from vartab */

	dvp = &pcb->pcb_difo->dtdo_vartab[pcb->pcb_asvidx++];
	stroff = dt_strtab_insert(pcb->pcb_strtab, idp->di_name);

	if (stroff == -1L)
		longjmp(pcb->pcb_jmpbuf, EDT_NOMEM);
	if (stroff > DIF_STROFF_MAX)
		longjmp(pcb->pcb_jmpbuf, EDT_STR2BIG);

	dvp->dtdv_name = (uint_t)stroff;
	dvp->dtdv_id = idp->di_id;
	dvp->dtdv_flags = 0;

	dvp->dtdv_kind = (idp->di_kind == DT_IDENT_ARRAY) ?
	    DIFV_KIND_ARRAY : DIFV_KIND_SCALAR;

	if (idp->di_flags & DT_IDFLG_LOCAL)
		dvp->dtdv_scope = DIFV_SCOPE_LOCAL;
	else if (idp->di_flags & DT_IDFLG_TLS)
		dvp->dtdv_scope = DIFV_SCOPE_THREAD;
	else
		dvp->dtdv_scope = DIFV_SCOPE_GLOBAL;

	if (idp->di_flags & DT_IDFLG_DIFR)
		dvp->dtdv_flags |= DIFV_F_REF;
	if (idp->di_flags & DT_IDFLG_DIFW)
		dvp->dtdv_flags |= DIFV_F_MOD;

	bzero(&dn, sizeof (dn));
	dt_node_type_assign(&dn, idp->di_ctfp, idp->di_type, B_FALSE);
	dt_node_diftype(pcb->pcb_hdl, &dn, &dvp->dtdv_type);

	idp->di_flags &= ~(DT_IDFLG_DIFR | DT_IDFLG_DIFW);
	return (0);
}