#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct bna_rxf {int ucast_pending_set; void (* cam_fltr_cbfn ) (struct bnad*,struct bna_rx*) ;int /*<<< orphan*/  cam_fltr_cbarg; TYPE_4__* ucast_pending_mac; TYPE_2__* rx; } ;
struct bna_rx {TYPE_3__* bna; struct bna_rxf rxf; } ;
typedef  enum bna_cb_status { ____Placeholder_bna_cb_status } bna_cb_status ;
struct TYPE_8__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  qe; } ;
struct TYPE_7__ {int /*<<< orphan*/  bnad; } ;
struct TYPE_6__ {TYPE_1__* bna; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucam_mod; } ;

/* Variables and functions */
 int BNA_CB_SUCCESS ; 
 int BNA_CB_UCAST_CAM_FULL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RXF_E_CONFIG ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* bna_ucam_mod_mac_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum bna_cb_status
bna_rx_ucast_set(struct bna_rx *rx, u8 *ucmac,
		 void (*cbfn)(struct bnad *, struct bna_rx *))
{
	struct bna_rxf *rxf = &rx->rxf;

	if (rxf->ucast_pending_mac == NULL) {
		rxf->ucast_pending_mac =
				bna_ucam_mod_mac_get(&rxf->rx->bna->ucam_mod);
		if (rxf->ucast_pending_mac == NULL)
			return BNA_CB_UCAST_CAM_FULL;
		bfa_q_qe_init(&rxf->ucast_pending_mac->qe);
	}

	memcpy(rxf->ucast_pending_mac->addr, ucmac, ETH_ALEN);
	rxf->ucast_pending_set = 1;
	rxf->cam_fltr_cbfn = cbfn;
	rxf->cam_fltr_cbarg = rx->bna->bnad;

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	return BNA_CB_SUCCESS;
}