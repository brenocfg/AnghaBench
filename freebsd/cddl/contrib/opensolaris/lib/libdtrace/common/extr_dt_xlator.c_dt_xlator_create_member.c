#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/  dx_dst_ctfp; TYPE_2__* dx_members; TYPE_2__* dx_nodes; int /*<<< orphan*/ * dx_hdl; } ;
typedef  TYPE_1__ dt_xlator_t ;
struct TYPE_6__ {scalar_t__ dn_kind; int /*<<< orphan*/ * dn_membname; struct TYPE_6__* dn_membexpr; struct TYPE_6__* dn_list; struct TYPE_6__* dn_link; struct TYPE_6__* dn_xmember; TYPE_1__* dn_xlator; int /*<<< orphan*/  dn_op; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DT_NODE_MEMBER ; 
 scalar_t__ DT_NODE_XLATOR ; 
 int /*<<< orphan*/  DT_TOK_XLATE ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dt_node_xalloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int
dt_xlator_create_member(const char *name, ctf_id_t type, ulong_t off, void *arg)
{
	dt_xlator_t *dxp = arg;
	dtrace_hdl_t *dtp = dxp->dx_hdl;
	dt_node_t *enp, *mnp;

	if ((enp = dt_node_xalloc(dtp, DT_NODE_XLATOR)) == NULL)
		return (dt_set_errno(dtp, EDT_NOMEM));

	enp->dn_link = dxp->dx_nodes;
	dxp->dx_nodes = enp;

	if ((mnp = dt_node_xalloc(dtp, DT_NODE_MEMBER)) == NULL)
		return (dt_set_errno(dtp, EDT_NOMEM));

	mnp->dn_link = dxp->dx_nodes;
	dxp->dx_nodes = mnp;

	/*
	 * For the member expression, we use a DT_NODE_XLATOR/TOK_XLATE whose
	 * xlator refers back to the translator and whose dn_xmember refers to
	 * the current member.  These refs will be used by dt_cg.c and dt_as.c.
	 */
	enp->dn_op = DT_TOK_XLATE;
	enp->dn_xlator = dxp;
	enp->dn_xmember = mnp;
	dt_node_type_assign(enp, dxp->dx_dst_ctfp, type, B_FALSE);

	/*
	 * For the member itself, we use a DT_NODE_MEMBER as usual with the
	 * appropriate name, output type, and member expression set to 'enp'.
	 */
	if (dxp->dx_members != NULL) {
		assert(enp->dn_link->dn_kind == DT_NODE_MEMBER);
		enp->dn_link->dn_list = mnp;
	} else
		dxp->dx_members = mnp;

	mnp->dn_membname = strdup(name);
	mnp->dn_membexpr = enp;
	dt_node_type_assign(mnp, dxp->dx_dst_ctfp, type, B_FALSE);

	if (mnp->dn_membname == NULL)
		return (dt_set_errno(dtp, EDT_NOMEM));

	return (0);
}