#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_9__ {int dn_flags; int dn_reg; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_10__ {int /*<<< orphan*/  cte_bits; } ;
typedef  TYPE_2__ ctf_encoding_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int /*<<< orphan*/  DIF_INSTR_COPYS (int,int,int) ; 
 int /*<<< orphan*/  DIF_INSTR_STORE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DIF_OP_STB ; 
 int /*<<< orphan*/  DIF_OP_STH ; 
 int /*<<< orphan*/  DIF_OP_STW ; 
 int /*<<< orphan*/  DIF_OP_STX ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int DT_NF_BITFIELD ; 
 int DT_NF_REF ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int NBBY ; 
 int P2ROUNDUP (int /*<<< orphan*/ ,int) ; 
 size_t clp2 (int) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int dt_cg_field_set (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t dt_node_type_size (TYPE_1__*) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_cg_store(dt_node_t *src, dt_irlist_t *dlp, dt_regset_t *drp, dt_node_t *dst)
{
	ctf_encoding_t e;
	dif_instr_t instr;
	size_t size;
	int reg;

	/*
	 * If we're loading a bit-field, the size of our store is found by
	 * rounding dst's cte_bits up to a byte boundary and then finding the
	 * nearest power of two to this value (see clp2(), above).
	 */
	if ((dst->dn_flags & DT_NF_BITFIELD) &&
	    ctf_type_encoding(dst->dn_ctfp, dst->dn_type, &e) != CTF_ERR)
		size = clp2(P2ROUNDUP(e.cte_bits, NBBY) / NBBY);
	else
		size = dt_node_type_size(src);

	if (src->dn_flags & DT_NF_REF) {
		reg = dt_regset_alloc(drp);
		dt_cg_setx(dlp, reg, size);
		instr = DIF_INSTR_COPYS(src->dn_reg, reg, dst->dn_reg);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
		dt_regset_free(drp, reg);
	} else {
		if (dst->dn_flags & DT_NF_BITFIELD)
			reg = dt_cg_field_set(src, dlp, drp, dst);
		else
			reg = src->dn_reg;

		switch (size) {
		case 1:
			instr = DIF_INSTR_STORE(DIF_OP_STB, reg, dst->dn_reg);
			break;
		case 2:
			instr = DIF_INSTR_STORE(DIF_OP_STH, reg, dst->dn_reg);
			break;
		case 4:
			instr = DIF_INSTR_STORE(DIF_OP_STW, reg, dst->dn_reg);
			break;
		case 8:
			instr = DIF_INSTR_STORE(DIF_OP_STX, reg, dst->dn_reg);
			break;
		default:
			xyerror(D_UNKNOWN, "internal error -- cg cannot store "
			    "size %lu when passed by value\n", (ulong_t)size);
		}
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

		if (dst->dn_flags & DT_NF_BITFIELD)
			dt_regset_free(drp, reg);
	}
}