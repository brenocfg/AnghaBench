#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_entries; } ;
struct bfi_enet_enable_req {TYPE_3__ mh; int /*<<< orphan*/  enable; } ;
struct TYPE_6__ {struct bfi_enet_enable_req admin_req; } ;
struct bna_ethport {int /*<<< orphan*/  msgq_cmd; TYPE_1__* bna; TYPE_2__ bfi_enet_cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  msgq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_H2I_PORT_ADMIN_UP_REQ ; 
 int /*<<< orphan*/  BFI_MC_ENET ; 
 int /*<<< orphan*/  BNA_STATUS_T_ENABLED ; 
 int /*<<< orphan*/  bfa_msgq_cmd_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_msgq_cmd_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  bfi_msgq_mhdr_set (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_msgq_num_cmd_entries (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_ethport_admin_up(struct bna_ethport *ethport)
{
	struct bfi_enet_enable_req *admin_up_req =
		&ethport->bfi_enet_cmd.admin_req;

	bfi_msgq_mhdr_set(admin_up_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_PORT_ADMIN_UP_REQ, 0, 0);
	admin_up_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(sizeof(struct bfi_enet_enable_req)));
	admin_up_req->enable = BNA_STATUS_T_ENABLED;

	bfa_msgq_cmd_set(&ethport->msgq_cmd, NULL, NULL,
		sizeof(struct bfi_enet_enable_req), &admin_up_req->mh);
	bfa_msgq_cmd_post(&ethport->bna->msgq, &ethport->msgq_cmd);
}