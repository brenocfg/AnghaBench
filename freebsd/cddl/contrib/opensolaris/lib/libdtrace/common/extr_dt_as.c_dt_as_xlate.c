#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  size_t uint_t ;
struct TYPE_12__ {int dt_xlatorid; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_13__ {size_t dtdo_len; size_t dtdo_xlmlen; TYPE_6__** dtdo_xlmtab; int /*<<< orphan*/ * dtdo_buf; } ;
typedef  TYPE_3__ dtrace_difo_t ;
struct TYPE_14__ {int dx_id; scalar_t__ dx_nmembers; } ;
typedef  TYPE_4__ dt_xlator_t ;
struct TYPE_15__ {int pcb_asxreflen; int /*<<< orphan*/ ** pcb_asxrefs; int /*<<< orphan*/  pcb_jmpbuf; TYPE_2__* pcb_hdl; } ;
typedef  TYPE_5__ dt_pcb_t ;
struct TYPE_16__ {scalar_t__ dn_kind; scalar_t__ dn_membid; TYPE_1__* dn_membexpr; } ;
typedef  TYPE_6__ dt_node_t ;
struct TYPE_11__ {scalar_t__ dn_kind; TYPE_4__* dn_xlator; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_SET (int /*<<< orphan*/ *,scalar_t__) ; 
 int BT_SIZEOFMAP (scalar_t__) ; 
 int /*<<< orphan*/  DIF_INSTR_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_INSTR_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIF_INSTR_XLATE (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ DT_NODE_MEMBER ; 
 scalar_t__ DT_NODE_XLATOR ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 void* dt_zalloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_as_xlate(dt_pcb_t *pcb, dtrace_difo_t *dp,
    uint_t i, uint_t xi, dt_node_t *dnp)
{
	dtrace_hdl_t *dtp = pcb->pcb_hdl;
	dt_xlator_t *dxp = dnp->dn_membexpr->dn_xlator;

	assert(i < dp->dtdo_len);
	assert(xi < dp->dtdo_xlmlen);

	assert(dnp->dn_kind == DT_NODE_MEMBER);
	assert(dnp->dn_membexpr->dn_kind == DT_NODE_XLATOR);

	assert(dxp->dx_id < dtp->dt_xlatorid);
	assert(dnp->dn_membid < dxp->dx_nmembers);

	if (pcb->pcb_asxrefs == NULL) {
		pcb->pcb_asxreflen = dtp->dt_xlatorid;
		pcb->pcb_asxrefs =
		    dt_zalloc(dtp, sizeof (ulong_t *) * pcb->pcb_asxreflen);
		if (pcb->pcb_asxrefs == NULL)
			longjmp(pcb->pcb_jmpbuf, EDT_NOMEM);
	}

	if (pcb->pcb_asxrefs[dxp->dx_id] == NULL) {
		pcb->pcb_asxrefs[dxp->dx_id] =
		    dt_zalloc(dtp, BT_SIZEOFMAP(dxp->dx_nmembers));
		if (pcb->pcb_asxrefs[dxp->dx_id] == NULL)
			longjmp(pcb->pcb_jmpbuf, EDT_NOMEM);
	}

	dp->dtdo_buf[i] = DIF_INSTR_XLATE(
	    DIF_INSTR_OP(dp->dtdo_buf[i]), xi, DIF_INSTR_RD(dp->dtdo_buf[i]));

	BT_SET(pcb->pcb_asxrefs[dxp->dx_id], dnp->dn_membid);
	dp->dtdo_xlmtab[xi] = dnp;
}