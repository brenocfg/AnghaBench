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
struct list_head {int dummy; } ;
struct bna_mac {int /*<<< orphan*/  qe; int /*<<< orphan*/  addr; } ;
struct bna_rxf {int ucast_active_set; int /*<<< orphan*/  ucast_active_q; int /*<<< orphan*/  ucast_pending_add_q; struct bna_mac ucast_active_mac; TYPE_3__* ucast_pending_mac; scalar_t__ ucast_pending_set; TYPE_2__* rx; int /*<<< orphan*/  ucast_pending_del_q; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__* bna; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucam_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_H2I_MAC_UCAST_ADD_REQ ; 
 int /*<<< orphan*/  BFI_ENET_H2I_MAC_UCAST_DEL_REQ ; 
 int /*<<< orphan*/  BFI_ENET_H2I_MAC_UCAST_SET_REQ ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_qe_init (struct list_head*) ; 
 int /*<<< orphan*/  bna_bfi_ucast_req (struct bna_rxf*,struct bna_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ucam_mod_mac_put (int /*<<< orphan*/ *,struct bna_mac*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bna_rxf_ucast_cfg_apply(struct bna_rxf *rxf)
{
	struct bna_mac *mac = NULL;
	struct list_head *qe;

	/* Delete MAC addresses previousely added */
	if (!list_empty(&rxf->ucast_pending_del_q)) {
		bfa_q_deq(&rxf->ucast_pending_del_q, &qe);
		bfa_q_qe_init(qe);
		mac = (struct bna_mac *)qe;
		bna_bfi_ucast_req(rxf, mac, BFI_ENET_H2I_MAC_UCAST_DEL_REQ);
		bna_ucam_mod_mac_put(&rxf->rx->bna->ucam_mod, mac);
		return 1;
	}

	/* Set default unicast MAC */
	if (rxf->ucast_pending_set) {
		rxf->ucast_pending_set = 0;
		memcpy(rxf->ucast_active_mac.addr,
			rxf->ucast_pending_mac->addr, ETH_ALEN);
		rxf->ucast_active_set = 1;
		bna_bfi_ucast_req(rxf, &rxf->ucast_active_mac,
			BFI_ENET_H2I_MAC_UCAST_SET_REQ);
		return 1;
	}

	/* Add additional MAC entries */
	if (!list_empty(&rxf->ucast_pending_add_q)) {
		bfa_q_deq(&rxf->ucast_pending_add_q, &qe);
		bfa_q_qe_init(qe);
		mac = (struct bna_mac *)qe;
		list_add_tail(&mac->qe, &rxf->ucast_active_q);
		bna_bfi_ucast_req(rxf, mac, BFI_ENET_H2I_MAC_UCAST_ADD_REQ);
		return 1;
	}

	return 0;
}