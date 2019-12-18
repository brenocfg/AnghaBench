#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfi_cee_get_req {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  mh; } ;
struct bfa_cee_attr {int dummy; } ;
struct TYPE_6__ {scalar_t__ msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  pa; } ;
struct TYPE_4__ {void* get_attr_cbarg; int /*<<< orphan*/  get_attr_cbfn; } ;
struct bfa_cee {int get_attr_pending; TYPE_3__ get_cfg_mb; int /*<<< orphan*/ * ioc; TYPE_2__ attr_dma; TYPE_1__ cbfn; struct bfa_cee_attr* attr; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;
typedef  int /*<<< orphan*/  bfa_cee_get_attr_cbfn_t ;

/* Variables and functions */
 int BFA_STATUS_DEVBUSY ; 
 int BFA_STATUS_IOC_FAILURE ; 
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFI_CEE_H2I_GET_CFG_REQ ; 
 int /*<<< orphan*/  BFI_MC_CEE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bfa_dma_be_addr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_nw_ioc_is_operational (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_queue (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum bfa_status
bfa_nw_cee_get_attr(struct bfa_cee *cee, struct bfa_cee_attr *attr,
		    bfa_cee_get_attr_cbfn_t cbfn, void *cbarg)
{
	struct bfi_cee_get_req *cmd;

	BUG_ON(!((cee != NULL) && (cee->ioc != NULL)));
	if (!bfa_nw_ioc_is_operational(cee->ioc))
		return BFA_STATUS_IOC_FAILURE;

	if (cee->get_attr_pending)
		return  BFA_STATUS_DEVBUSY;

	cee->get_attr_pending = true;
	cmd = (struct bfi_cee_get_req *) cee->get_cfg_mb.msg;
	cee->attr = attr;
	cee->cbfn.get_attr_cbfn = cbfn;
	cee->cbfn.get_attr_cbarg = cbarg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_CFG_REQ,
		    bfa_ioc_portid(cee->ioc));
	bfa_dma_be_addr_set(cmd->dma_addr, cee->attr_dma.pa);
	bfa_nw_ioc_mbox_queue(cee->ioc, &cee->get_cfg_mb, NULL, NULL);

	return BFA_STATUS_OK;
}