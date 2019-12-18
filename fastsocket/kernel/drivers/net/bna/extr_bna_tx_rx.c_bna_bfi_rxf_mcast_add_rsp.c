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
typedef  int /*<<< orphan*/  u8 ;
struct bfi_enet_mcast_add_req {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_2__ {struct bfi_enet_mcast_add_req mcast_add_req; } ;
struct bna_rxf {TYPE_1__ bfi_enet_cmd; } ;
struct bfi_msgq_mhdr {int dummy; } ;
struct bfi_enet_mcast_add_rsp {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXF_E_FW_RESP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rxf_mchandle_attach (struct bna_rxf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

void
bna_bfi_rxf_mcast_add_rsp(struct bna_rxf *rxf,
			struct bfi_msgq_mhdr *msghdr)
{
	struct bfi_enet_mcast_add_req *req =
		&rxf->bfi_enet_cmd.mcast_add_req;
	struct bfi_enet_mcast_add_rsp *rsp =
		(struct bfi_enet_mcast_add_rsp *)msghdr;

	bna_rxf_mchandle_attach(rxf, (u8 *)&req->mac_addr,
		ntohs(rsp->handle));
	bfa_fsm_send_event(rxf, RXF_E_FW_RESP);
}