#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* num_entries; } ;
struct bfi_enet_rit_req {TYPE_4__ mh; int /*<<< orphan*/ * table; void* size; } ;
struct TYPE_6__ {struct bfi_enet_rit_req rit_req; } ;
struct bna_rxf {int /*<<< orphan*/  msgq_cmd; TYPE_3__* rx; int /*<<< orphan*/  rit_size; int /*<<< orphan*/  rit; TYPE_1__ bfi_enet_cmd; } ;
struct TYPE_8__ {TYPE_2__* bna; int /*<<< orphan*/  rid; } ;
struct TYPE_7__ {int /*<<< orphan*/  msgq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_H2I_RIT_CFG_REQ ; 
 int /*<<< orphan*/  BFI_MC_ENET ; 
 int /*<<< orphan*/  bfa_msgq_cmd_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_msgq_cmd_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/  bfi_msgq_mhdr_set (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_msgq_num_cmd_entries (int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_rit_cfg(struct bna_rxf *rxf)
{
	struct bfi_enet_rit_req *req = &rxf->bfi_enet_cmd.rit_req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RIT_CFG_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(sizeof(struct bfi_enet_rit_req)));
	req->size = htons(rxf->rit_size);
	memcpy(&req->table[0], rxf->rit, rxf->rit_size);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, NULL, NULL,
		sizeof(struct bfi_enet_rit_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
}