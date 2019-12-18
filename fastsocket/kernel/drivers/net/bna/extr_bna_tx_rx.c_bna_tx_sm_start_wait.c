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
struct bna_tx {int flags; } ;
typedef  enum bna_tx_event { ____Placeholder_bna_tx_event } bna_tx_event ;

/* Variables and functions */
 int BNA_TX_F_BW_UPDATED ; 
 int BNA_TX_F_PRIO_CHANGED ; 
#define  TX_E_BW_UPDATE 132 
#define  TX_E_FAIL 131 
#define  TX_E_PRIO_CHANGE 130 
#define  TX_E_STARTED 129 
#define  TX_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_tx_sm_prio_stop_wait ; 
 int /*<<< orphan*/  bna_tx_sm_started ; 
 int /*<<< orphan*/  bna_tx_sm_stop_wait ; 
 int /*<<< orphan*/  bna_tx_sm_stopped ; 

__attribute__((used)) static void
bna_tx_sm_start_wait(struct bna_tx *tx, enum bna_tx_event event)
{
	switch (event) {
	case TX_E_STOP:
		tx->flags &= ~(BNA_TX_F_PRIO_CHANGED | BNA_TX_F_BW_UPDATED);
		bfa_fsm_set_state(tx, bna_tx_sm_stop_wait);
		break;

	case TX_E_FAIL:
		tx->flags &= ~(BNA_TX_F_PRIO_CHANGED | BNA_TX_F_BW_UPDATED);
		bfa_fsm_set_state(tx, bna_tx_sm_stopped);
		break;

	case TX_E_STARTED:
		if (tx->flags & (BNA_TX_F_PRIO_CHANGED | BNA_TX_F_BW_UPDATED)) {
			tx->flags &= ~(BNA_TX_F_PRIO_CHANGED |
				BNA_TX_F_BW_UPDATED);
			bfa_fsm_set_state(tx, bna_tx_sm_prio_stop_wait);
		} else
			bfa_fsm_set_state(tx, bna_tx_sm_started);
		break;

	case TX_E_PRIO_CHANGE:
		tx->flags |=  BNA_TX_F_PRIO_CHANGED;
		break;

	case TX_E_BW_UPDATE:
		tx->flags |= BNA_TX_F_BW_UPDATED;
		break;

	default:
		bfa_sm_fault(event);
	}
}