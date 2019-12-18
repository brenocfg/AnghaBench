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
struct bna_tx {TYPE_1__* bna; int /*<<< orphan*/  (* tx_cleanup_cbfn ) (int /*<<< orphan*/ ,struct bna_tx*) ;} ;
typedef  enum bna_tx_event { ____Placeholder_bna_tx_event } bna_tx_event ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
#define  TX_E_BW_UPDATE 132 
#define  TX_E_FAIL 131 
#define  TX_E_PRIO_CHANGE 130 
#define  TX_E_STARTED 129 
#define  TX_E_STOPPED 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_tx_enet_stop (struct bna_tx*) ; 
 int /*<<< orphan*/  bna_tx_sm_cleanup_wait ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bna_tx*) ; 

__attribute__((used)) static void
bna_tx_sm_stop_wait(struct bna_tx *tx, enum bna_tx_event event)
{
	switch (event) {
	case TX_E_FAIL:
	case TX_E_STOPPED:
		bfa_fsm_set_state(tx, bna_tx_sm_cleanup_wait);
		tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
		break;

	case TX_E_STARTED:
		/**
		 * We are here due to start_wait -> stop_wait transition on
		 * TX_E_STOP event
		 */
		bna_tx_enet_stop(tx);
		break;

	case TX_E_PRIO_CHANGE:
	case TX_E_BW_UPDATE:
		/* No-op */
		break;

	default:
		bfa_sm_fault(event);
	}
}