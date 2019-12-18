#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfi_enet_enable_req {int enable; } ;
struct TYPE_4__ {struct bfi_enet_enable_req admin_req; } ;
struct bna_ethport {TYPE_1__* bna; int /*<<< orphan*/  (* link_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  link_status; int /*<<< orphan*/  flags; TYPE_2__ bfi_enet_cmd; } ;
struct bfi_msgq_mhdr {int dummy; } ;
struct bfi_enet_rsp {int /*<<< orphan*/  error; } ;
struct TYPE_3__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_CMD_OK ; 
 int /*<<< orphan*/  BNA_ETHPORT_F_PORT_ENABLED ; 
 int /*<<< orphan*/  BNA_LINK_DOWN ; 
#define  BNA_STATUS_T_DISABLED 129 
#define  BNA_STATUS_T_ENABLED 128 
 int /*<<< orphan*/  ETHPORT_E_FWRESP_DOWN ; 
 int /*<<< orphan*/  ETHPORT_E_FWRESP_UP_FAIL ; 
 int /*<<< orphan*/  ETHPORT_E_FWRESP_UP_OK ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_ethport_admin_rsp(struct bna_ethport *ethport,
				struct bfi_msgq_mhdr *msghdr)
{
	struct bfi_enet_enable_req *admin_req =
		&ethport->bfi_enet_cmd.admin_req;
	struct bfi_enet_rsp *rsp = (struct bfi_enet_rsp *)msghdr;

	switch (admin_req->enable) {
	case BNA_STATUS_T_ENABLED:
		if (rsp->error == BFI_ENET_CMD_OK)
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_OK);
		else {
			ethport->flags &= ~BNA_ETHPORT_F_PORT_ENABLED;
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_FAIL);
		}
		break;

	case BNA_STATUS_T_DISABLED:
		bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_DOWN);
		ethport->link_status = BNA_LINK_DOWN;
		ethport->link_cbfn(ethport->bna->bnad, BNA_LINK_DOWN);
		break;
	}
}