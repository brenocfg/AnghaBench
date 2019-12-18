#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* dx_ident; } ;
typedef  TYPE_4__ dt_xlator_t ;
struct TYPE_18__ {int /*<<< orphan*/ * pcb_regs; int /*<<< orphan*/  pcb_ir; TYPE_6__* pcb_dret; int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_strtab; int /*<<< orphan*/ * pcb_inttab; TYPE_2__* pcb_hdl; } ;
typedef  TYPE_5__ dt_pcb_t ;
struct TYPE_19__ {scalar_t__ dn_kind; int dn_reg; struct TYPE_19__* dn_membexpr; TYPE_4__* dn_membxlator; } ;
typedef  TYPE_6__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_ident_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_20__ {int /*<<< orphan*/  pcb_hdl; } ;
struct TYPE_16__ {int di_id; int /*<<< orphan*/  di_flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  dtc_difintregs; } ;
struct TYPE_15__ {TYPE_1__ dt_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  DIF_INSTR_RET (int) ; 
 int /*<<< orphan*/  DT_IDENT_XLPTR ; 
 int /*<<< orphan*/  DT_IDENT_XLSOU ; 
 int /*<<< orphan*/  DT_IDFLG_CGREG ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 scalar_t__ DT_NODE_MEMBER ; 
 int /*<<< orphan*/  D_CG_DYN ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnerror (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dt_cg_node (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dt_cg_xlate_expand (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_inttab_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_inttab_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_irlist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_irlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_node_resolve (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_assert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_regset_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dt_regset_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_strtab_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_strtab_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* yypcb ; 

void
dt_cg(dt_pcb_t *pcb, dt_node_t *dnp)
{
	dif_instr_t instr;
	dt_xlator_t *dxp;
	dt_ident_t *idp;

	if (pcb->pcb_regs == NULL && (pcb->pcb_regs =
	    dt_regset_create(pcb->pcb_hdl->dt_conf.dtc_difintregs)) == NULL)
		longjmp(pcb->pcb_jmpbuf, EDT_NOMEM);

	dt_regset_reset(pcb->pcb_regs);
	(void) dt_regset_alloc(pcb->pcb_regs); /* allocate %r0 */

	if (pcb->pcb_inttab != NULL)
		dt_inttab_destroy(pcb->pcb_inttab);

	if ((pcb->pcb_inttab = dt_inttab_create(yypcb->pcb_hdl)) == NULL)
		longjmp(pcb->pcb_jmpbuf, EDT_NOMEM);

	if (pcb->pcb_strtab != NULL)
		dt_strtab_destroy(pcb->pcb_strtab);

	if ((pcb->pcb_strtab = dt_strtab_create(BUFSIZ)) == NULL)
		longjmp(pcb->pcb_jmpbuf, EDT_NOMEM);

	dt_irlist_destroy(&pcb->pcb_ir);
	dt_irlist_create(&pcb->pcb_ir);

	assert(pcb->pcb_dret == NULL);
	pcb->pcb_dret = dnp;

	if (dt_node_resolve(dnp, DT_IDENT_XLPTR) != NULL) {
		dnerror(dnp, D_CG_DYN, "expression cannot evaluate to result "
		    "of a translated pointer\n");
	}

	/*
	 * If we're generating code for a translator body, assign the input
	 * parameter to the first available register (i.e. caller passes %r1).
	 */
	if (dnp->dn_kind == DT_NODE_MEMBER) {
		dxp = dnp->dn_membxlator;
		dnp = dnp->dn_membexpr;

		dxp->dx_ident->di_flags |= DT_IDFLG_CGREG;
		dxp->dx_ident->di_id = dt_regset_alloc(pcb->pcb_regs);
	}

	dt_cg_node(dnp, &pcb->pcb_ir, pcb->pcb_regs);

	if ((idp = dt_node_resolve(dnp, DT_IDENT_XLSOU)) != NULL) {
		int reg = dt_cg_xlate_expand(dnp, idp,
		    &pcb->pcb_ir, pcb->pcb_regs);
		dt_regset_free(pcb->pcb_regs, dnp->dn_reg);
		dnp->dn_reg = reg;
	}

	instr = DIF_INSTR_RET(dnp->dn_reg);
	dt_regset_free(pcb->pcb_regs, dnp->dn_reg);
	dt_irlist_append(&pcb->pcb_ir, dt_cg_node_alloc(DT_LBL_NONE, instr));

	if (dnp->dn_kind == DT_NODE_MEMBER) {
		dt_regset_free(pcb->pcb_regs, dxp->dx_ident->di_id);
		dxp->dx_ident->di_id = 0;
		dxp->dx_ident->di_flags &= ~DT_IDFLG_CGREG;
	}

	dt_regset_free(pcb->pcb_regs, 0);
	dt_regset_assert_free(pcb->pcb_regs);
}