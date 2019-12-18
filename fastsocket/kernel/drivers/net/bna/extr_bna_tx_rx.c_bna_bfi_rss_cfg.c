#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * toeplitz_hash_key; int /*<<< orphan*/  hash_mask; int /*<<< orphan*/  hash_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  num_entries; } ;
struct TYPE_9__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;
struct bfi_enet_rss_cfg_req {TYPE_6__ mh; TYPE_2__ cfg; } ;
struct TYPE_8__ {struct bfi_enet_rss_cfg_req rss_req; } ;
struct bna_rxf {int /*<<< orphan*/  msgq_cmd; TYPE_5__* rx; TYPE_3__ rss_cfg; TYPE_1__ bfi_enet_cmd; } ;
struct TYPE_12__ {TYPE_4__* bna; int /*<<< orphan*/  rid; } ;
struct TYPE_11__ {int /*<<< orphan*/  msgq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_H2I_RSS_CFG_REQ ; 
 int BFI_ENET_RSS_KEY_LEN ; 
 int /*<<< orphan*/  BFI_MC_ENET ; 
 int /*<<< orphan*/  bfa_msgq_cmd_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_msgq_cmd_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_6__*) ; 
 int /*<<< orphan*/  bfi_msgq_mhdr_set (TYPE_6__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_msgq_num_cmd_entries (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_rss_cfg(struct bna_rxf *rxf)
{
	struct bfi_enet_rss_cfg_req *req = &rxf->bfi_enet_cmd.rss_req;
	int i;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RSS_CFG_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(sizeof(struct bfi_enet_rss_cfg_req)));
	req->cfg.type = rxf->rss_cfg.hash_type;
	req->cfg.mask = rxf->rss_cfg.hash_mask;
	for (i = 0; i < BFI_ENET_RSS_KEY_LEN; i++)
		req->cfg.key[i] =
			htonl(rxf->rss_cfg.toeplitz_hash_key[i]);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, NULL, NULL,
		sizeof(struct bfi_enet_rss_cfg_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
}