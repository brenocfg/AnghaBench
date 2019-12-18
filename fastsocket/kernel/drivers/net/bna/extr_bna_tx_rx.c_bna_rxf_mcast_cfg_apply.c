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
struct bna_rxf {int /*<<< orphan*/  mcast_active_q; int /*<<< orphan*/  mcast_pending_add_q; TYPE_2__* rx; int /*<<< orphan*/  mcast_pending_del_q; } ;
struct bna_mac {int /*<<< orphan*/  qe; } ;
struct TYPE_4__ {TYPE_1__* bna; } ;
struct TYPE_3__ {int /*<<< orphan*/  mcam_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_HARD_CLEANUP ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_qe_init (struct list_head*) ; 
 int /*<<< orphan*/  bna_bfi_mcast_add_req (struct bna_rxf*,struct bna_mac*) ; 
 int /*<<< orphan*/  bna_mcam_mod_mac_put (int /*<<< orphan*/ *,struct bna_mac*) ; 
 int bna_rxf_mcast_del (struct bna_rxf*,struct bna_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bna_rxf_mcast_cfg_apply(struct bna_rxf *rxf)
{
	struct bna_mac *mac = NULL;
	struct list_head *qe;
	int ret;

	/* Delete multicast entries previousely added */
	while (!list_empty(&rxf->mcast_pending_del_q)) {
		bfa_q_deq(&rxf->mcast_pending_del_q, &qe);
		bfa_q_qe_init(qe);
		mac = (struct bna_mac *)qe;
		ret = bna_rxf_mcast_del(rxf, mac, BNA_HARD_CLEANUP);
		bna_mcam_mod_mac_put(&rxf->rx->bna->mcam_mod, mac);
		if (ret)
			return ret;
	}

	/* Add multicast entries */
	if (!list_empty(&rxf->mcast_pending_add_q)) {
		bfa_q_deq(&rxf->mcast_pending_add_q, &qe);
		bfa_q_qe_init(qe);
		mac = (struct bna_mac *)qe;
		list_add_tail(&mac->qe, &rxf->mcast_active_q);
		bna_bfi_mcast_add_req(rxf, mac);
		return 1;
	}

	return 0;
}