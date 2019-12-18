#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bna_rxf {int rxmode_active; int /*<<< orphan*/  rxmode_pending_bitmask; int /*<<< orphan*/  rxmode_pending; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;

/* Variables and functions */
 int BNA_HARD_CLEANUP ; 
 int BNA_RXMODE_ALLMULTI ; 
 int /*<<< orphan*/  BNA_STATUS_T_ENABLED ; 
 int /*<<< orphan*/  allmulti_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allmulti_inactive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_bfi_mcast_filter_req (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_allmulti_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bna_rxf_allmulti_cfg_reset(struct bna_rxf *rxf, enum bna_cleanup_type cleanup)
{
	/* Clear pending allmulti mode disable */
	if (is_allmulti_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask)) {
		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active &= ~BNA_RXMODE_ALLMULTI;
		if (cleanup == BNA_HARD_CLEANUP) {
			bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_ENABLED);
			return 1;
		}
	}

	/* Move allmulti mode config from active -> pending */
	if (rxf->rxmode_active & BNA_RXMODE_ALLMULTI) {
		allmulti_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_bitmask);
		rxf->rxmode_active &= ~BNA_RXMODE_ALLMULTI;
		if (cleanup == BNA_HARD_CLEANUP) {
			bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_ENABLED);
			return 1;
		}
	}

	return 0;
}