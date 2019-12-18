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
struct bna_rxf {int /*<<< orphan*/  rxmode_active; int /*<<< orphan*/  rxmode_pending_bitmask; int /*<<< orphan*/  rxmode_pending; TYPE_1__* rx; } ;
struct bna {int /*<<< orphan*/  promisc_rid; } ;
struct TYPE_2__ {struct bna* bna; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_INVALID_RID ; 
 int /*<<< orphan*/  BNA_RXMODE_PROMISC ; 
 int /*<<< orphan*/  BNA_STATUS_T_DISABLED ; 
 int /*<<< orphan*/  BNA_STATUS_T_ENABLED ; 
 int /*<<< orphan*/  bna_bfi_rx_promisc_req (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_promisc_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_promisc_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  promisc_inactive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bna_rxf_promisc_cfg_apply(struct bna_rxf *rxf)
{
	struct bna *bna = rxf->rx->bna;

	/* Enable/disable promiscuous mode */
	if (is_promisc_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask)) {
		/* move promisc configuration from pending -> active */
		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active |= BNA_RXMODE_PROMISC;
		bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_ENABLED);
		return 1;
	} else if (is_promisc_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask)) {
		/* move promisc configuration from pending -> active */
		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active &= ~BNA_RXMODE_PROMISC;
		bna->promisc_rid = BFI_INVALID_RID;
		bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_DISABLED);
		return 1;
	}

	return 0;
}