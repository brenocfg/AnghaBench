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
struct bna_rx {scalar_t__ fsm; TYPE_1__* bna; int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/  (* stop_cbfn ) (int /*<<< orphan*/ *,struct bna_rx*) ;int /*<<< orphan*/  rx_flags; } ;
typedef  scalar_t__ bfa_fsm_t ;
struct TYPE_2__ {int /*<<< orphan*/  rx_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_RX_F_ENET_STARTED ; 
 int /*<<< orphan*/  RX_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rx_mod_cb_rx_stopped (int /*<<< orphan*/ *,struct bna_rx*) ; 
 scalar_t__ bna_rx_sm_stopped ; 

__attribute__((used)) static void
bna_rx_stop(struct bna_rx *rx)
{
	rx->rx_flags &= ~BNA_RX_F_ENET_STARTED;
	if (rx->fsm == (bfa_fsm_t) bna_rx_sm_stopped)
		bna_rx_mod_cb_rx_stopped(&rx->bna->rx_mod, rx);
	else {
		rx->stop_cbfn = bna_rx_mod_cb_rx_stopped;
		rx->stop_cbarg = &rx->bna->rx_mod;
		bfa_fsm_send_event(rx, RX_E_STOP);
	}
}