#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
#define  CTF_K_FUNCTION 130 
#define  CTF_K_STRUCT 129 
#define  CTF_K_UNION 128 
 int DT_NF_COOKED ; 
 int /*<<< orphan*/  assert (int) ; 
 int ctf_type_compat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_integer (TYPE_1__ const*) ; 
 int dt_node_is_ptrcompat (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dt_node_is_stack (TYPE_1__ const*) ; 
 scalar_t__ dt_node_is_strcompat (TYPE_1__ const*) ; 
 scalar_t__ dt_node_is_symaddr (TYPE_1__ const*) ; 
 scalar_t__ dt_node_is_usymaddr (TYPE_1__ const*) ; 

int
dt_node_is_argcompat(const dt_node_t *lp, const dt_node_t *rp)
{
	ctf_file_t *lfp = lp->dn_ctfp;
	ctf_file_t *rfp = rp->dn_ctfp;

	assert(lp->dn_flags & DT_NF_COOKED);
	assert(rp->dn_flags & DT_NF_COOKED);

	if (dt_node_is_integer(lp) && dt_node_is_integer(rp))
		return (1); /* integer types are compatible */

	if (dt_node_is_strcompat(lp) && dt_node_is_strcompat(rp))
		return (1); /* string types are compatible */

	if (dt_node_is_stack(lp) && dt_node_is_stack(rp))
		return (1); /* stack types are compatible */

	if (dt_node_is_symaddr(lp) && dt_node_is_symaddr(rp))
		return (1); /* symaddr types are compatible */

	if (dt_node_is_usymaddr(lp) && dt_node_is_usymaddr(rp))
		return (1); /* usymaddr types are compatible */

	switch (ctf_type_kind(lfp, ctf_type_resolve(lfp, lp->dn_type))) {
	case CTF_K_FUNCTION:
	case CTF_K_STRUCT:
	case CTF_K_UNION:
		return (ctf_type_compat(lfp, lp->dn_type, rfp, rp->dn_type));
	default:
		return (dt_node_is_ptrcompat(lp, rp, NULL, NULL));
	}
}