#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort_t ;
struct TYPE_11__ {TYPE_1__* dt_ddefs; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_12__ {scalar_t__ dn_kind; unsigned long long dn_value; int dn_flags; struct TYPE_12__* dn_child; scalar_t__ dn_op; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_13__ {TYPE_2__* pcb_hdl; } ;
struct TYPE_10__ {int /*<<< orphan*/  dm_ctfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int DT_NF_SIGNED ; 
 scalar_t__ DT_NODE_INT ; 
 int /*<<< orphan*/  DT_NODE_OP1 ; 
 scalar_t__ DT_NODE_STRING ; 
 scalar_t__ DT_NODE_TYPE ; 
#define  DT_TOK_BNEG 131 
#define  DT_TOK_INEG 130 
 scalar_t__ DT_TOK_INT ; 
#define  DT_TOK_IPOS 129 
#define  DT_TOK_LNEG 128 
 int DT_TOK_SIZEOF ; 
 int /*<<< orphan*/  D_SIZEOF_TYPE ; 
 size_t NBBY ; 
 int USHRT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctf_lookup_by_name (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t dt_node_type_size (TYPE_3__*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* yypcb ; 

dt_node_t *
dt_node_op1(int op, dt_node_t *cp)
{
	dt_node_t *dnp;

	if (cp->dn_kind == DT_NODE_INT) {
		switch (op) {
		case DT_TOK_INEG:
			/*
			 * If we're negating an unsigned integer, zero out any
			 * extra top bits to truncate the value to the size of
			 * the effective type determined by dt_node_int().
			 */
			cp->dn_value = -cp->dn_value;
			if (!(cp->dn_flags & DT_NF_SIGNED)) {
				cp->dn_value &= ~0ULL >>
				    (64 - dt_node_type_size(cp) * NBBY);
			}
			/*FALLTHRU*/
		case DT_TOK_IPOS:
			return (cp);
		case DT_TOK_BNEG:
			cp->dn_value = ~cp->dn_value;
			return (cp);
		case DT_TOK_LNEG:
			cp->dn_value = !cp->dn_value;
			return (cp);
		}
	}

	/*
	 * If sizeof is applied to a type_name or string constant, we can
	 * transform 'cp' into an integer constant in the node construction
	 * pass so that it can then be used for arithmetic in this pass.
	 */
	if (op == DT_TOK_SIZEOF &&
	    (cp->dn_kind == DT_NODE_STRING || cp->dn_kind == DT_NODE_TYPE)) {
		dtrace_hdl_t *dtp = yypcb->pcb_hdl;
		size_t size = dt_node_type_size(cp);

		if (size == 0) {
			xyerror(D_SIZEOF_TYPE, "cannot apply sizeof to an "
			    "operand of unknown size\n");
		}

		dt_node_type_assign(cp, dtp->dt_ddefs->dm_ctfp,
		    ctf_lookup_by_name(dtp->dt_ddefs->dm_ctfp, "size_t"),
		    B_FALSE);

		cp->dn_kind = DT_NODE_INT;
		cp->dn_op = DT_TOK_INT;
		cp->dn_value = size;

		return (cp);
	}

	dnp = dt_node_alloc(DT_NODE_OP1);
	assert(op <= USHRT_MAX);
	dnp->dn_op = (ushort_t)op;
	dnp->dn_child = cp;

	return (dnp);
}