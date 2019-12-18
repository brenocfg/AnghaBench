#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_25__ {TYPE_2__* dx_ident; int /*<<< orphan*/  dx_dst_ctfp; int /*<<< orphan*/  dx_dst_base; TYPE_4__* dx_members; } ;
typedef  TYPE_3__ dt_xlator_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_26__ {scalar_t__ dn_kind; int dn_reg; int dn_flags; struct TYPE_26__* dn_left; int /*<<< orphan*/  dn_args; int /*<<< orphan*/  dn_ident; struct TYPE_26__* dn_right; int /*<<< orphan*/  dn_membname; int /*<<< orphan*/  dn_string; struct TYPE_26__* dn_membexpr; struct TYPE_26__* dn_list; int /*<<< orphan*/  dn_op; } ;
typedef  TYPE_4__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
struct TYPE_27__ {scalar_t__ di_kind; int /*<<< orphan*/  di_id; int /*<<< orphan*/  di_flags; TYPE_3__* di_data; } ;
typedef  TYPE_5__ dt_ident_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_28__ {int ctm_offset; } ;
typedef  TYPE_6__ ctf_membinfo_t ;
struct TYPE_29__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_1__* pcb_hdl; } ;
struct TYPE_24__ {int di_id; int /*<<< orphan*/  di_flags; } ;
struct TYPE_23__ {int /*<<< orphan*/  dt_ctferr; } ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int /*<<< orphan*/  DIF_INSTR_ALLOCS (int,int) ; 
 int /*<<< orphan*/  DIF_INSTR_FMT (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DIF_INSTR_STV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DIF_OP_ADD ; 
 scalar_t__ DT_IDENT_ARRAY ; 
 int /*<<< orphan*/  DT_IDENT_XLSOU ; 
 int /*<<< orphan*/  DT_IDFLG_CGREG ; 
 int /*<<< orphan*/  DT_IDFLG_DIFW ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int DT_NF_LVALUE ; 
 int DT_NF_REF ; 
 int DT_NF_WRITABLE ; 
 scalar_t__ DT_NODE_IDENT ; 
 scalar_t__ DT_NODE_OP2 ; 
 scalar_t__ DT_NODE_VAR ; 
 int /*<<< orphan*/  DT_TOK_DOT ; 
 int /*<<< orphan*/  DT_TOK_IDENT ; 
 int /*<<< orphan*/  EDT_CTF ; 
 int NBBY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_member_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int ctf_type_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_arglist (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_cg_node (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dt_cg_store (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dt_cg_stvar (TYPE_5__*) ; 
 int /*<<< orphan*/  dt_cg_typecast (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* dt_ident_resolve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* dt_node_resolve (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_propagate (TYPE_4__*,TYPE_4__*) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* yypcb ; 

__attribute__((used)) static void
dt_cg_asgn_op(dt_node_t *dnp, dt_irlist_t *dlp, dt_regset_t *drp)
{
	dif_instr_t instr;
	dt_ident_t *idp;

	/*
	 * If we are performing a structure assignment of a translated type,
	 * we must instantiate all members and create a snapshot of the object
	 * in scratch space.  We allocs a chunk of memory, generate code for
	 * each member, and then set dnp->dn_reg to the scratch object address.
	 */
	if ((idp = dt_node_resolve(dnp->dn_right, DT_IDENT_XLSOU)) != NULL) {
		ctf_membinfo_t ctm;
		dt_xlator_t *dxp = idp->di_data;
		dt_node_t *mnp, dn, mn;
		int r1, r2;

		/*
		 * Create two fake dt_node_t's representing operator "." and a
		 * right-hand identifier child node.  These will be repeatedly
		 * modified according to each instantiated member so that we
		 * can pass them to dt_cg_store() and effect a member store.
		 */
		bzero(&dn, sizeof (dt_node_t));
		dn.dn_kind = DT_NODE_OP2;
		dn.dn_op = DT_TOK_DOT;
		dn.dn_left = dnp;
		dn.dn_right = &mn;

		bzero(&mn, sizeof (dt_node_t));
		mn.dn_kind = DT_NODE_IDENT;
		mn.dn_op = DT_TOK_IDENT;

		/*
		 * Allocate a register for our scratch data pointer.  First we
		 * set it to the size of our data structure, and then replace
		 * it with the result of an allocs of the specified size.
		 */
		r1 = dt_regset_alloc(drp);
		dt_cg_setx(dlp, r1,
		    ctf_type_size(dxp->dx_dst_ctfp, dxp->dx_dst_base));

		instr = DIF_INSTR_ALLOCS(r1, r1);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

		/*
		 * When dt_cg_asgn_op() is called, we have already generated
		 * code for dnp->dn_right, which is the translator input.  We
		 * now associate this register with the translator's input
		 * identifier so it can be referenced during our member loop.
		 */
		dxp->dx_ident->di_flags |= DT_IDFLG_CGREG;
		dxp->dx_ident->di_id = dnp->dn_right->dn_reg;

		for (mnp = dxp->dx_members; mnp != NULL; mnp = mnp->dn_list) {
			/*
			 * Generate code for the translator member expression,
			 * and then cast the result to the member type.
			 */
			dt_cg_node(mnp->dn_membexpr, dlp, drp);
			mnp->dn_reg = mnp->dn_membexpr->dn_reg;
			dt_cg_typecast(mnp->dn_membexpr, mnp, dlp, drp);

			/*
			 * Ask CTF for the offset of the member so we can store
			 * to the appropriate offset.  This call has already
			 * been done once by the parser, so it should succeed.
			 */
			if (ctf_member_info(dxp->dx_dst_ctfp, dxp->dx_dst_base,
			    mnp->dn_membname, &ctm) == CTF_ERR) {
				yypcb->pcb_hdl->dt_ctferr =
				    ctf_errno(dxp->dx_dst_ctfp);
				longjmp(yypcb->pcb_jmpbuf, EDT_CTF);
			}

			/*
			 * If the destination member is at offset 0, store the
			 * result directly to r1 (the scratch buffer address).
			 * Otherwise allocate another temporary for the offset
			 * and add r1 to it before storing the result.
			 */
			if (ctm.ctm_offset != 0) {
				r2 = dt_regset_alloc(drp);

				/*
				 * Add the member offset rounded down to the
				 * nearest byte.  If the offset was not aligned
				 * on a byte boundary, this member is a bit-
				 * field and dt_cg_store() will handle masking.
				 */
				dt_cg_setx(dlp, r2, ctm.ctm_offset / NBBY);
				instr = DIF_INSTR_FMT(DIF_OP_ADD, r1, r2, r2);
				dt_irlist_append(dlp,
				    dt_cg_node_alloc(DT_LBL_NONE, instr));

				dt_node_type_propagate(mnp, &dn);
				dn.dn_right->dn_string = mnp->dn_membname;
				dn.dn_reg = r2;

				dt_cg_store(mnp, dlp, drp, &dn);
				dt_regset_free(drp, r2);

			} else {
				dt_node_type_propagate(mnp, &dn);
				dn.dn_right->dn_string = mnp->dn_membname;
				dn.dn_reg = r1;

				dt_cg_store(mnp, dlp, drp, &dn);
			}

			dt_regset_free(drp, mnp->dn_reg);
		}

		dxp->dx_ident->di_flags &= ~DT_IDFLG_CGREG;
		dxp->dx_ident->di_id = 0;

		if (dnp->dn_right->dn_reg != -1)
			dt_regset_free(drp, dnp->dn_right->dn_reg);

		assert(dnp->dn_reg == dnp->dn_right->dn_reg);
		dnp->dn_reg = r1;
	}

	/*
	 * If we are storing to a variable, generate an stv instruction from
	 * the variable specified by the identifier.  If we are storing to a
	 * memory address, generate code again for the left-hand side using
	 * DT_NF_REF to get the address, and then generate a store to it.
	 * In both paths, we assume dnp->dn_reg already has the new value.
	 */
	if (dnp->dn_left->dn_kind == DT_NODE_VAR) {
		idp = dt_ident_resolve(dnp->dn_left->dn_ident);

		if (idp->di_kind == DT_IDENT_ARRAY)
			dt_cg_arglist(idp, dnp->dn_left->dn_args, dlp, drp);

		idp->di_flags |= DT_IDFLG_DIFW;
		instr = DIF_INSTR_STV(dt_cg_stvar(idp),
		    idp->di_id, dnp->dn_reg);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	} else {
		uint_t rbit = dnp->dn_left->dn_flags & DT_NF_REF;

		assert(dnp->dn_left->dn_flags & DT_NF_WRITABLE);
		assert(dnp->dn_left->dn_flags & DT_NF_LVALUE);

		dnp->dn_left->dn_flags |= DT_NF_REF; /* force pass-by-ref */

		dt_cg_node(dnp->dn_left, dlp, drp);
		dt_cg_store(dnp, dlp, drp, dnp->dn_left);
		dt_regset_free(drp, dnp->dn_left->dn_reg);

		dnp->dn_left->dn_flags &= ~DT_NF_REF;
		dnp->dn_left->dn_flags |= rbit;
	}
}