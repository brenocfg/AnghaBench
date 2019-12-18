#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_12__ {int dn_reg; TYPE_1__* dn_left; TYPE_8__* dn_child; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
struct TYPE_13__ {int /*<<< orphan*/  di_id; int /*<<< orphan*/  di_flags; } ;
typedef  TYPE_3__ dt_ident_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_14__ {int dn_reg; scalar_t__ dn_kind; int dn_flags; int /*<<< orphan*/  dn_ident; } ;
struct TYPE_11__ {int dn_flags; } ;

/* Variables and functions */
 scalar_t__ CTF_K_POINTER ; 
 int /*<<< orphan*/  DIF_INSTR_FMT (int,int,int,int) ; 
 int /*<<< orphan*/  DIF_INSTR_STV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DT_IDFLG_DIFW ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int DT_NF_LVALUE ; 
 int DT_NF_REF ; 
 int DT_NF_WRITABLE ; 
 scalar_t__ DT_NODE_VAR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ctf_type_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_node (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dt_cg_store (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  dt_cg_stvar (TYPE_3__*) ; 
 TYPE_3__* dt_ident_resolve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_pointer (TYPE_2__*) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dt_cg_postarith_op(dt_node_t *dnp, dt_irlist_t *dlp,
    dt_regset_t *drp, uint_t op)
{
	ctf_file_t *ctfp = dnp->dn_ctfp;
	dif_instr_t instr;
	ctf_id_t type;
	ssize_t size = 1;
	int nreg;

	if (dt_node_is_pointer(dnp)) {
		type = ctf_type_resolve(ctfp, dnp->dn_type);
		assert(ctf_type_kind(ctfp, type) == CTF_K_POINTER);
		size = ctf_type_size(ctfp, ctf_type_reference(ctfp, type));
	}

	dt_cg_node(dnp->dn_child, dlp, drp);
	dnp->dn_reg = dnp->dn_child->dn_reg;

	nreg = dt_regset_alloc(drp);
	dt_cg_setx(dlp, nreg, size);
	instr = DIF_INSTR_FMT(op, dnp->dn_reg, nreg, nreg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));

	/*
	 * If we are modifying a variable, generate an stv instruction from
	 * the variable specified by the identifier.  If we are storing to a
	 * memory address, generate code again for the left-hand side using
	 * DT_NF_REF to get the address, and then generate a store to it.
	 * In both paths, we store the value from 'nreg' (the new value).
	 */
	if (dnp->dn_child->dn_kind == DT_NODE_VAR) {
		dt_ident_t *idp = dt_ident_resolve(dnp->dn_child->dn_ident);

		idp->di_flags |= DT_IDFLG_DIFW;
		instr = DIF_INSTR_STV(dt_cg_stvar(idp), idp->di_id, nreg);
		dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	} else {
		uint_t rbit = dnp->dn_child->dn_flags & DT_NF_REF;
		int oreg = dnp->dn_reg;

		assert(dnp->dn_child->dn_flags & DT_NF_WRITABLE);
		assert(dnp->dn_child->dn_flags & DT_NF_LVALUE);

		dnp->dn_child->dn_flags |= DT_NF_REF; /* force pass-by-ref */
		dt_cg_node(dnp->dn_child, dlp, drp);

		dnp->dn_reg = nreg;
		dt_cg_store(dnp, dlp, drp, dnp->dn_child);
		dnp->dn_reg = oreg;

		dt_regset_free(drp, dnp->dn_child->dn_reg);
		dnp->dn_left->dn_flags &= ~DT_NF_REF;
		dnp->dn_left->dn_flags |= rbit;
	}

	dt_regset_free(drp, nreg);
}