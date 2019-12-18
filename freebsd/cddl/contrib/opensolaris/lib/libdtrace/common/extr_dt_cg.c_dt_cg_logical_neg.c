#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_4__ {int /*<<< orphan*/  dn_reg; TYPE_2__* dn_child; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dn_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_BRANCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_INSTR_MOV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_INSTR_NOP ; 
 int /*<<< orphan*/  DIF_INSTR_TST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_OP_BA ; 
 int /*<<< orphan*/  DIF_OP_BE ; 
 int /*<<< orphan*/  DIF_REG_R0 ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int /*<<< orphan*/  dt_cg_node (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_xsetx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_irlist_label (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_cg_logical_neg(dt_node_t *dnp, dt_irlist_t *dlp, dt_regset_t *drp)
{
	uint_t lbl_zero = dt_irlist_label(dlp);
	uint_t lbl_post = dt_irlist_label(dlp);

	dif_instr_t instr;

	dt_cg_node(dnp->dn_child, dlp, drp);
	dnp->dn_reg = dnp->dn_child->dn_reg;

	instr = DIF_INSTR_TST(dnp->dn_reg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	instr = DIF_INSTR_BRANCH(DIF_OP_BE, lbl_zero);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	instr = DIF_INSTR_MOV(DIF_REG_R0, dnp->dn_reg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	instr = DIF_INSTR_BRANCH(DIF_OP_BA, lbl_post);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_cg_xsetx(dlp, NULL, lbl_zero, dnp->dn_reg, 1);
	dt_irlist_append(dlp, dt_cg_node_alloc(lbl_post, DIF_INSTR_NOP));
}