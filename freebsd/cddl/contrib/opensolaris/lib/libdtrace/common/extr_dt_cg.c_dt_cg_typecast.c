#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_6__ {int dn_flags; int /*<<< orphan*/  dn_reg; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_FMT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_OP_SLL ; 
 int /*<<< orphan*/  DIF_OP_SRA ; 
 int /*<<< orphan*/  DIF_OP_SRL ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int DT_NF_SIGNED ; 
 int NBBY ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_is_scalar (TYPE_1__ const*) ; 
 size_t dt_node_type_size (TYPE_1__ const*) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dt_cg_typecast(const dt_node_t *src, const dt_node_t *dst,
    dt_irlist_t *dlp, dt_regset_t *drp)
{
	size_t srcsize = dt_node_type_size(src);
	size_t dstsize = dt_node_type_size(dst);

	dif_instr_t instr;
	int rg;

	if (!dt_node_is_scalar(dst))
		return; /* not a scalar */
	if (dstsize == srcsize &&
	    ((src->dn_flags ^ dst->dn_flags) & DT_NF_SIGNED) != 0)
		return; /* not narrowing or changing signed-ness */
	if (dstsize > srcsize && (src->dn_flags & DT_NF_SIGNED) == 0)
		return; /* nothing to do in this case */

	rg = dt_regset_alloc(drp);

	if (dstsize > srcsize) {
		int n = sizeof (uint64_t) * NBBY - srcsize * NBBY;
		int s = (dstsize - srcsize) * NBBY;

		dt_cg_setx(dlp, rg, n);

		instr = DIF_INSTR_FMT(DIF_OP_SLL, src->dn_reg, rg, dst->dn_reg);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

		if ((dst->dn_flags & DT_NF_SIGNED) || n == s) {
			instr = DIF_INSTR_FMT(DIF_OP_SRA,
			    dst->dn_reg, rg, dst->dn_reg);
			dt_irlist_append(dlp,
			    dt_cg_node_alloc(DT_LBL_NONE, instr));
		} else {
			dt_cg_setx(dlp, rg, s);
			instr = DIF_INSTR_FMT(DIF_OP_SRA,
			    dst->dn_reg, rg, dst->dn_reg);
			dt_irlist_append(dlp,
			    dt_cg_node_alloc(DT_LBL_NONE, instr));
			dt_cg_setx(dlp, rg, n - s);
			instr = DIF_INSTR_FMT(DIF_OP_SRL,
			    dst->dn_reg, rg, dst->dn_reg);
			dt_irlist_append(dlp,
			    dt_cg_node_alloc(DT_LBL_NONE, instr));
		}
	} else if (dstsize != sizeof (uint64_t)) {
		int n = sizeof (uint64_t) * NBBY - dstsize * NBBY;

		dt_cg_setx(dlp, rg, n);

		instr = DIF_INSTR_FMT(DIF_OP_SLL, src->dn_reg, rg, dst->dn_reg);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

		instr = DIF_INSTR_FMT((dst->dn_flags & DT_NF_SIGNED) ?
		    DIF_OP_SRA : DIF_OP_SRL, dst->dn_reg, rg, dst->dn_reg);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	}

	dt_regset_free(drp, rg);
}