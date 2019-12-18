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
struct list_head {int dummy; } ;
struct bna_mac {int dummy; } ;
struct bna_rxf {int ucast_pending_set; struct bna_mac ucast_active_mac; scalar_t__ ucast_active_set; int /*<<< orphan*/  ucast_pending_add_q; int /*<<< orphan*/  ucast_active_q; TYPE_2__* rx; int /*<<< orphan*/  ucast_pending_del_q; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_4__ {TYPE_1__* bna; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucam_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_H2I_MAC_UCAST_CLR_REQ ; 
 int /*<<< orphan*/  BFI_ENET_H2I_MAC_UCAST_DEL_REQ ; 
 int BNA_HARD_CLEANUP ; 
 int BNA_SOFT_CLEANUP ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_qe_init (struct list_head*) ; 
 int /*<<< orphan*/  bna_bfi_ucast_req (struct bna_rxf*,struct bna_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ucam_mod_mac_put (int /*<<< orphan*/ *,struct bna_mac*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bna_rxf_ucast_cfg_reset(struct bna_rxf *rxf, enum bna_cleanup_type cleanup)
{
	struct list_head *qe;
	struct bna_mac *mac;

	/* Throw away delete pending ucast entries */
	while (!list_empty(&rxf->ucast_pending_del_q)) {
		bfa_q_deq(&rxf->ucast_pending_del_q, &qe);
		bfa_q_qe_init(qe);
		mac = (struct bna_mac *)qe;
		if (cleanup == BNA_SOFT_CLEANUP)
			bna_ucam_mod_mac_put(&rxf->rx->bna->ucam_mod, mac);
		else {
			bna_bfi_ucast_req(rxf, mac,
				BFI_ENET_H2I_MAC_UCAST_DEL_REQ);
			bna_ucam_mod_mac_put(&rxf->rx->bna->ucam_mod, mac);
			return 1;
		}
	}

	/* Move active ucast entries to pending_add_q */
	while (!list_empty(&rxf->ucast_active_q)) {
		bfa_q_deq(&rxf->ucast_active_q, &qe);
		bfa_q_qe_init(qe);
		list_add_tail(qe, &rxf->ucast_pending_add_q);
		if (cleanup == BNA_HARD_CLEANUP) {
			mac = (struct bna_mac *)qe;
			bna_bfi_ucast_req(rxf, mac,
				BFI_ENET_H2I_MAC_UCAST_DEL_REQ);
			return 1;
		}
	}

	if (rxf->ucast_active_set) {
		rxf->ucast_pending_set = 1;
		rxf->ucast_active_set = 0;
		if (cleanup == BNA_HARD_CLEANUP) {
			bna_bfi_ucast_req(rxf, &rxf->ucast_active_mac,
				BFI_ENET_H2I_MAC_UCAST_CLR_REQ);
			return 1;
		}
	}

	return 0;
}