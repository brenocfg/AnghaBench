#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_7__ {int /*<<< orphan*/  dn_reg; TYPE_6__* dn_left; TYPE_6__* dn_right; TYPE_6__* dn_expr; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_8__ {void* di_instr; } ;
typedef  TYPE_2__ dt_irnode_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  void* dif_instr_t ;
struct TYPE_9__ {int /*<<< orphan*/  dn_reg; } ;

/* Variables and functions */
 void* DIF_INSTR_BRANCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* DIF_INSTR_MOV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* DIF_INSTR_NOP ; 
 void* DIF_INSTR_TST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_OP_BA ; 
 int /*<<< orphan*/  DIF_OP_BE ; 
 int /*<<< orphan*/  DIF_REG_R0 ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int /*<<< orphan*/  dt_cg_node (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* dt_cg_node_alloc (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_irlist_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_cg_ternary_op(dt_node_t *dnp, dt_irlist_t *dlp, dt_regset_t *drp)
{
	uint_t lbl_false = dt_irlist_label(dlp);
	uint_t lbl_post = dt_irlist_label(dlp);

	dif_instr_t instr;
	dt_irnode_t *dip;

	dt_cg_node(dnp->dn_expr, dlp, drp);
	instr = DIF_INSTR_TST(dnp->dn_expr->dn_reg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	dt_regset_free(drp, dnp->dn_expr->dn_reg);

	instr = DIF_INSTR_BRANCH(DIF_OP_BE, lbl_false);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_cg_node(dnp->dn_left, dlp, drp);
	instr = DIF_INSTR_MOV(dnp->dn_left->dn_reg, DIF_REG_R0);
	dip = dt_cg_node_alloc(DT_LBL_NONE, instr); /* save dip for below */
	dt_irlist_append(dlp, dip);
	dt_regset_free(drp, dnp->dn_left->dn_reg);

	instr = DIF_INSTR_BRANCH(DIF_OP_BA, lbl_post);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_irlist_append(dlp, dt_cg_node_alloc(lbl_false, DIF_INSTR_NOP));
	dt_cg_node(dnp->dn_right, dlp, drp);
	dnp->dn_reg = dnp->dn_right->dn_reg;

	/*
	 * Now that dn_reg is assigned, reach back and patch the correct MOV
	 * instruction into the tail of dn_left.  We know dn_reg was unused
	 * at that point because otherwise dn_right couldn't have allocated it.
	 */
	dip->di_instr = DIF_INSTR_MOV(dnp->dn_left->dn_reg, dnp->dn_reg);
	dt_irlist_append(dlp, dt_cg_node_alloc(lbl_post, DIF_INSTR_NOP));
}