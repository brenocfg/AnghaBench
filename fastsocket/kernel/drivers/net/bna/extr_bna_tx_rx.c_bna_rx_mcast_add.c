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
typedef  int /*<<< orphan*/  u8 ;
struct bna_rxf {void (* cam_fltr_cbfn ) (struct bnad*,struct bna_rx*) ;struct bnad* cam_fltr_cbarg; int /*<<< orphan*/  mcast_pending_add_q; TYPE_2__* rx; int /*<<< orphan*/  mcast_active_q; } ;
struct bna_rx {TYPE_3__* bna; struct bna_rxf rxf; } ;
struct bna_mac {int /*<<< orphan*/  qe; int /*<<< orphan*/  addr; } ;
typedef  enum bna_cb_status { ____Placeholder_bna_cb_status } bna_cb_status ;
struct TYPE_6__ {struct bnad* bnad; } ;
struct TYPE_5__ {TYPE_1__* bna; } ;
struct TYPE_4__ {int /*<<< orphan*/  mcam_mod; } ;

/* Variables and functions */
 int BNA_CB_MCAST_LIST_FULL ; 
 int BNA_CB_SUCCESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RXF_E_CONFIG ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 scalar_t__ bna_mac_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bna_mac* bna_mcam_mod_mac_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum bna_cb_status
bna_rx_mcast_add(struct bna_rx *rx, u8 *addr,
		 void (*cbfn)(struct bnad *, struct bna_rx *))
{
	struct bna_rxf *rxf = &rx->rxf;
	struct bna_mac *mac;

	/* Check if already added or pending addition */
	if (bna_mac_find(&rxf->mcast_active_q, addr) ||
		bna_mac_find(&rxf->mcast_pending_add_q, addr)) {
		if (cbfn)
			cbfn(rx->bna->bnad, rx);
		return BNA_CB_SUCCESS;
	}

	mac = bna_mcam_mod_mac_get(&rxf->rx->bna->mcam_mod);
	if (mac == NULL)
		return BNA_CB_MCAST_LIST_FULL;
	bfa_q_qe_init(&mac->qe);
	memcpy(mac->addr, addr, ETH_ALEN);
	list_add_tail(&mac->qe, &rxf->mcast_pending_add_q);

	rxf->cam_fltr_cbfn = cbfn;
	rxf->cam_fltr_cbarg = rx->bna->bnad;

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	return BNA_CB_SUCCESS;
}