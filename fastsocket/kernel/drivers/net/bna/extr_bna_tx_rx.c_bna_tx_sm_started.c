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
struct bna_tx {TYPE_1__* bna; int /*<<< orphan*/  (* tx_cleanup_cbfn ) (int /*<<< orphan*/ ,struct bna_tx*) ;int /*<<< orphan*/  (* tx_stall_cbfn ) (int /*<<< orphan*/ ,struct bna_tx*) ;} ;
typedef  enum bna_tx_event { ____Placeholder_bna_tx_event } bna_tx_event ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
#define  TX_E_BW_UPDATE 131 
#define  TX_E_FAIL 130 
#define  TX_E_PRIO_CHANGE 129 
#define  TX_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_tx_enet_stop (struct bna_tx*) ; 
 int /*<<< orphan*/  bna_tx_sm_failed ; 
 int /*<<< orphan*/  bna_tx_sm_prio_stop_wait ; 
 int /*<<< orphan*/  bna_tx_sm_stop_wait ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bna_tx*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct bna_tx*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct bna_tx*) ; 

__attribute__((used)) static void
bna_tx_sm_started(struct bna_tx *tx, enum bna_tx_event event)
{
	switch (event) {
	case TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_stop_wait);
		tx->tx_stall_cbfn(tx->bna->bnad, tx);
		bna_tx_enet_stop(tx);
		break;

	case TX_E_FAIL:
		bfa_fsm_set_state(tx, bna_tx_sm_failed);
		tx->tx_stall_cbfn(tx->bna->bnad, tx);
		tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
		break;

	case TX_E_PRIO_CHANGE:
	case TX_E_BW_UPDATE:
		bfa_fsm_set_state(tx, bna_tx_sm_prio_stop_wait);
		break;

	default:
		bfa_sm_fault(event);
	}
}