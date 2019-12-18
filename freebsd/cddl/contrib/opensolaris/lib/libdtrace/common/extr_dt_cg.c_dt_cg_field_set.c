#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_16__ {scalar_t__ dn_op; int dn_reg; TYPE_2__* dn_right; TYPE_1__* dn_left; } ;
typedef  TYPE_4__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_17__ {int ctm_offset; int /*<<< orphan*/  ctm_type; } ;
typedef  TYPE_5__ ctf_membinfo_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_18__ {int cte_bits; } ;
typedef  TYPE_6__ ctf_encoding_t ;
struct TYPE_19__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_3__* pcb_hdl; } ;
struct TYPE_15__ {int /*<<< orphan*/  dt_ctferr; } ;
struct TYPE_14__ {scalar_t__ dn_kind; int /*<<< orphan*/  dn_string; } ;
struct TYPE_13__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_FMT (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DIF_INSTR_LOAD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DIF_OP_AND ; 
 int /*<<< orphan*/  DIF_OP_OR ; 
 int /*<<< orphan*/  DIF_OP_SLL ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 scalar_t__ DT_NODE_IDENT ; 
 scalar_t__ DT_TOK_DOT ; 
 scalar_t__ DT_TOK_PTR ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  EDT_CTF ; 
 int NBBY ; 
 int P2ROUNDUP (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int clp2 (int) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_load (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_cg_membinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* yypcb ; 

__attribute__((used)) static int
dt_cg_field_set(dt_node_t *src, dt_irlist_t *dlp,
    dt_regset_t *drp, dt_node_t *dst)
{
	uint64_t cmask, fmask, shift;
	dif_instr_t instr;
	int r1, r2, r3;

	ctf_membinfo_t m;
	ctf_encoding_t e;
	ctf_file_t *fp, *ofp;
	ctf_id_t type;

	assert(dst->dn_op == DT_TOK_PTR || dst->dn_op == DT_TOK_DOT);
	assert(dst->dn_right->dn_kind == DT_NODE_IDENT);

	fp = dst->dn_left->dn_ctfp;
	type = ctf_type_resolve(fp, dst->dn_left->dn_type);

	if (dst->dn_op == DT_TOK_PTR) {
		type = ctf_type_reference(fp, type);
		type = ctf_type_resolve(fp, type);
	}

	if ((fp = dt_cg_membinfo(ofp = fp, type,
	    dst->dn_right->dn_string, &m)) == NULL) {
		yypcb->pcb_hdl->dt_ctferr = ctf_errno(ofp);
		longjmp(yypcb->pcb_jmpbuf, EDT_CTF);
	}

	if (ctf_type_encoding(fp, m.ctm_type, &e) != 0 || e.cte_bits > 64) {
		xyerror(D_UNKNOWN, "cg: bad field: off %lu type <%ld> "
		    "bits %u\n", m.ctm_offset, m.ctm_type, e.cte_bits);
	}

	r1 = dt_regset_alloc(drp);
	r2 = dt_regset_alloc(drp);
	r3 = dt_regset_alloc(drp);

	/*
	 * Compute shifts and masks.  We need to compute "shift" as the amount
	 * we need to shift left to position our field in the containing word.
	 * Refer to the comments in dt_cg_field_get(), above, for more info.
	 * We then compute fmask as the mask that truncates the value in the
	 * input register to width cte_bits, and cmask as the mask used to
	 * pass through the containing bits and zero the field bits.
	 */
#if BYTE_ORDER == _BIG_ENDIAN
	shift = clp2(P2ROUNDUP(e.cte_bits, NBBY) / NBBY) * NBBY -
	    (m.ctm_offset % NBBY + e.cte_bits);
#else
	shift = m.ctm_offset % NBBY;
#endif
	fmask = (1ULL << e.cte_bits) - 1;
	cmask = ~(fmask << shift);

	instr = DIF_INSTR_LOAD(
	    dt_cg_load(dst, fp, m.ctm_type), dst->dn_reg, r1);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_cg_setx(dlp, r2, cmask);
	instr = DIF_INSTR_FMT(DIF_OP_AND, r1, r2, r1);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_cg_setx(dlp, r2, fmask);
	instr = DIF_INSTR_FMT(DIF_OP_AND, src->dn_reg, r2, r2);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_cg_setx(dlp, r3, shift);
	instr = DIF_INSTR_FMT(DIF_OP_SLL, r2, r3, r2);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	instr = DIF_INSTR_FMT(DIF_OP_OR, r1, r2, r1);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	dt_regset_free(drp, r3);
	dt_regset_free(drp, r2);

	return (r1);
}