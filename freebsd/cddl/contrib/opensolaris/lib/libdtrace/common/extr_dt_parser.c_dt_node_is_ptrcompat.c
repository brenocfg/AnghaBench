#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_8__ {int dn_flags; scalar_t__ dn_kind; scalar_t__ dn_value; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
typedef  int /*<<< orphan*/  ctf_encoding_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctr_contents; } ;
typedef  TYPE_2__ ctf_arinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 scalar_t__ CTF_K_ARRAY ; 
 scalar_t__ CTF_K_POINTER ; 
 int DT_NF_COOKED ; 
 int DT_NF_USERLAND ; 
 scalar_t__ DT_NODE_INT ; 
 scalar_t__ IS_VOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_array_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ctf_type_compat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_dynamic (TYPE_1__ const*) ; 
 int dt_node_is_integer (TYPE_1__ const*) ; 

int
dt_node_is_ptrcompat(const dt_node_t *lp, const dt_node_t *rp,
    ctf_file_t **fpp, ctf_id_t *tp)
{
	ctf_file_t *lfp = lp->dn_ctfp;
	ctf_file_t *rfp = rp->dn_ctfp;

	ctf_id_t lbase = CTF_ERR, rbase = CTF_ERR;
	ctf_id_t lref = CTF_ERR, rref = CTF_ERR;

	int lp_is_void, rp_is_void, lp_is_int, rp_is_int, compat;
	uint_t lkind, rkind;
	ctf_encoding_t e;
	ctf_arinfo_t r;

	assert(lp->dn_flags & DT_NF_COOKED);
	assert(rp->dn_flags & DT_NF_COOKED);

	if (dt_node_is_dynamic(lp) || dt_node_is_dynamic(rp))
		return (0); /* fail if either node is a dynamic variable */

	lp_is_int = dt_node_is_integer(lp);
	rp_is_int = dt_node_is_integer(rp);

	if (lp_is_int && rp_is_int)
		return (0); /* fail if both nodes are integers */

	if (lp_is_int && (lp->dn_kind != DT_NODE_INT || lp->dn_value != 0))
		return (0); /* fail if lp is an integer that isn't 0 constant */

	if (rp_is_int && (rp->dn_kind != DT_NODE_INT || rp->dn_value != 0))
		return (0); /* fail if rp is an integer that isn't 0 constant */

	if ((lp_is_int == 0 && rp_is_int == 0) && (
	    (lp->dn_flags & DT_NF_USERLAND) ^ (rp->dn_flags & DT_NF_USERLAND)))
		return (0); /* fail if only one pointer is a userland address */

	/*
	 * Resolve the left-hand and right-hand types to their base type, and
	 * then resolve the referenced type as well (assuming the base type
	 * is CTF_K_POINTER or CTF_K_ARRAY).  Otherwise [lr]ref = CTF_ERR.
	 */
	if (!lp_is_int) {
		lbase = ctf_type_resolve(lfp, lp->dn_type);
		lkind = ctf_type_kind(lfp, lbase);

		if (lkind == CTF_K_POINTER) {
			lref = ctf_type_resolve(lfp,
			    ctf_type_reference(lfp, lbase));
		} else if (lkind == CTF_K_ARRAY &&
		    ctf_array_info(lfp, lbase, &r) == 0) {
			lref = ctf_type_resolve(lfp, r.ctr_contents);
		}
	}

	if (!rp_is_int) {
		rbase = ctf_type_resolve(rfp, rp->dn_type);
		rkind = ctf_type_kind(rfp, rbase);

		if (rkind == CTF_K_POINTER) {
			rref = ctf_type_resolve(rfp,
			    ctf_type_reference(rfp, rbase));
		} else if (rkind == CTF_K_ARRAY &&
		    ctf_array_info(rfp, rbase, &r) == 0) {
			rref = ctf_type_resolve(rfp, r.ctr_contents);
		}
	}

	/*
	 * We know that one or the other type may still be a zero-valued
	 * integer constant.  To simplify the code below, set the integer
	 * type variables equal to the non-integer types and proceed.
	 */
	if (lp_is_int) {
		lbase = rbase;
		lkind = rkind;
		lref = rref;
		lfp = rfp;
	} else if (rp_is_int) {
		rbase = lbase;
		rkind = lkind;
		rref = lref;
		rfp = lfp;
	}

	lp_is_void = ctf_type_encoding(lfp, lref, &e) == 0 && IS_VOID(e);
	rp_is_void = ctf_type_encoding(rfp, rref, &e) == 0 && IS_VOID(e);

	/*
	 * The types are compatible if both are pointers to the same type, or
	 * if either pointer is a void pointer.  If they are compatible, set
	 * tp to point to the more specific pointer type and return it.
	 */
	compat = (lkind == CTF_K_POINTER || lkind == CTF_K_ARRAY) &&
	    (rkind == CTF_K_POINTER || rkind == CTF_K_ARRAY) &&
	    (lp_is_void || rp_is_void || ctf_type_compat(lfp, lref, rfp, rref));

	if (compat) {
		if (fpp != NULL)
			*fpp = rp_is_void ? lfp : rfp;
		if (tp != NULL)
			*tp = rp_is_void ? lbase : rbase;
	}

	return (compat);
}