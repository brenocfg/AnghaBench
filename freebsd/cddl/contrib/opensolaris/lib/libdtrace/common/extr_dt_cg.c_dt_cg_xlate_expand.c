#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int dtxl_dreg; int /*<<< orphan*/  dtxl_sreg; int /*<<< orphan*/ * dtxl_drp; int /*<<< orphan*/ * dtxl_dlp; int /*<<< orphan*/ * dtxl_idp; } ;
typedef  TYPE_2__ dt_xlmemb_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_8__ {TYPE_1__* dn_ident; int /*<<< orphan*/  dn_reg; } ;
typedef  TYPE_3__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dt_ident_t ;
struct TYPE_6__ {int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_CALL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DIF_INSTR_FLUSHTS ; 
 int /*<<< orphan*/  DIF_INSTR_PUSHTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DIF_OP_PUSHTV ; 
 int /*<<< orphan*/  DIF_REG_R0 ; 
 int /*<<< orphan*/  DIF_SUBR_ALLOCA ; 
 int /*<<< orphan*/  DIF_TYPE_CTF ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int /*<<< orphan*/  ctf_member_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t ctf_type_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  dt_cg_xlate_member ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dt_cg_xlate_expand(dt_node_t *dnp, dt_ident_t *idp, dt_irlist_t *dlp,
    dt_regset_t *drp)
{
	dt_xlmemb_t dlm;
	uint32_t instr;
	int dreg;
	size_t size;

	dreg = dt_regset_alloc(drp);
	size = ctf_type_size(dnp->dn_ident->di_ctfp, dnp->dn_ident->di_type);

	/* Call alloca() to create the buffer. */
	dt_cg_setx(dlp, dreg, size);

	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, DIF_INSTR_FLUSHTS));

	instr = DIF_INSTR_PUSHTS(DIF_OP_PUSHTV, DIF_TYPE_CTF, DIF_REG_R0, dreg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	instr = DIF_INSTR_CALL(DIF_SUBR_ALLOCA, dreg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	/* Generate the translation for each member. */
	dlm.dtxl_idp = idp;
	dlm.dtxl_dlp = dlp;
	dlm.dtxl_drp = drp;
	dlm.dtxl_sreg = dnp->dn_reg;
	dlm.dtxl_dreg = dreg;
	(void) ctf_member_iter(dnp->dn_ident->di_ctfp,
	    dnp->dn_ident->di_type, dt_cg_xlate_member,
	    &dlm);

	return (dreg);
}