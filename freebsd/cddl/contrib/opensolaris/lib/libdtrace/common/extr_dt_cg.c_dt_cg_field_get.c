#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_9__ {scalar_t__ dn_op; int dn_flags; TYPE_1__* dn_left; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_10__ {int ctm_offset; int /*<<< orphan*/  ctm_type; } ;
typedef  TYPE_3__ ctf_membinfo_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_11__ {int cte_bits; } ;
typedef  TYPE_4__ ctf_encoding_t ;
struct TYPE_8__ {int dn_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_FMT (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DIF_OP_AND ; 
 int /*<<< orphan*/  DIF_OP_SLL ; 
 int /*<<< orphan*/  DIF_OP_SRA ; 
 int /*<<< orphan*/  DIF_OP_SRL ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int DT_NF_SIGNED ; 
 scalar_t__ DT_TOK_DOT ; 
 scalar_t__ DT_TOK_PTR ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int NBBY ; 
 int P2ROUNDUP (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int clp2 (int) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,unsigned long long) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dt_cg_field_get(dt_node_t *dnp, dt_irlist_t *dlp, dt_regset_t *drp,
    ctf_file_t *fp, const ctf_membinfo_t *mp)
{
	ctf_encoding_t e;
	dif_instr_t instr;
	uint64_t shift;
	int r1, r2;

	if (ctf_type_encoding(fp, mp->ctm_type, &e) != 0 || e.cte_bits > 64) {
		xyerror(D_UNKNOWN, "cg: bad field: off %lu type <%ld> "
		    "bits %u\n", mp->ctm_offset, mp->ctm_type, e.cte_bits);
	}

	assert(dnp->dn_op == DT_TOK_PTR || dnp->dn_op == DT_TOK_DOT);
	r1 = dnp->dn_left->dn_reg;
	r2 = dt_regset_alloc(drp);

	/*
	 * On little-endian architectures, ctm_offset counts from the right so
	 * ctm_offset % NBBY itself is the amount we want to shift right to
	 * move the value bits to the little end of the register to mask them.
	 * On big-endian architectures, ctm_offset counts from the left so we
	 * must subtract (ctm_offset % NBBY + cte_bits) from the size in bits
	 * we used for the load.  The size of our load in turn is found by
	 * rounding cte_bits up to a byte boundary and then finding the
	 * nearest power of two to this value (see clp2(), above).  These
	 * properties are used to compute shift as USHIFT or SSHIFT, below.
	 */
	if (dnp->dn_flags & DT_NF_SIGNED) {
#if BYTE_ORDER == _BIG_ENDIAN
		shift = clp2(P2ROUNDUP(e.cte_bits, NBBY) / NBBY) * NBBY -
		    mp->ctm_offset % NBBY;
#else
		shift = mp->ctm_offset % NBBY + e.cte_bits;
#endif
		dt_cg_setx(dlp, r2, 64 - shift);
		instr = DIF_INSTR_FMT(DIF_OP_SLL, r1, r2, r1);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

		dt_cg_setx(dlp, r2, 64 - e.cte_bits);
		instr = DIF_INSTR_FMT(DIF_OP_SRA, r1, r2, r1);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	} else {
#if BYTE_ORDER == _BIG_ENDIAN
		shift = clp2(P2ROUNDUP(e.cte_bits, NBBY) / NBBY) * NBBY -
		    (mp->ctm_offset % NBBY + e.cte_bits);
#else
		shift = mp->ctm_offset % NBBY;
#endif
		dt_cg_setx(dlp, r2, shift);
		instr = DIF_INSTR_FMT(DIF_OP_SRL, r1, r2, r1);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

		dt_cg_setx(dlp, r2, (1ULL << e.cte_bits) - 1);
		instr = DIF_INSTR_FMT(DIF_OP_AND, r1, r2, r1);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	}

	dt_regset_free(drp, r2);
}