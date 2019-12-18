#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfi_enet_diag_lb_req {int enable; } ;
struct TYPE_2__ {struct bfi_enet_diag_lb_req lpbk_req; } ;
struct bna_ethport {int /*<<< orphan*/  flags; TYPE_1__ bfi_enet_cmd; } ;
struct bfi_msgq_mhdr {int dummy; } ;
struct bfi_enet_rsp {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_CMD_OK ; 
 int /*<<< orphan*/  BNA_ETHPORT_F_ADMIN_UP ; 
#define  BNA_STATUS_T_DISABLED 129 
#define  BNA_STATUS_T_ENABLED 128 
 int /*<<< orphan*/  ETHPORT_E_FWRESP_DOWN ; 
 int /*<<< orphan*/  ETHPORT_E_FWRESP_UP_FAIL ; 
 int /*<<< orphan*/  ETHPORT_E_FWRESP_UP_OK ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ethport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_ethport_lpbk_rsp(struct bna_ethport *ethport,
				struct bfi_msgq_mhdr *msghdr)
{
	struct bfi_enet_diag_lb_req *diag_lb_req =
		&ethport->bfi_enet_cmd.lpbk_req;
	struct bfi_enet_rsp *rsp = (struct bfi_enet_rsp *)msghdr;

	switch (diag_lb_req->enable) {
	case BNA_STATUS_T_ENABLED:
		if (rsp->error == BFI_ENET_CMD_OK)
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_OK);
		else {
			ethport->flags &= ~BNA_ETHPORT_F_ADMIN_UP;
			bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_UP_FAIL);
		}
		break;

	case BNA_STATUS_T_DISABLED:
		bfa_fsm_send_event(ethport, ETHPORT_E_FWRESP_DOWN);
		break;
	}
}