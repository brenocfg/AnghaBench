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
struct bna_tx {int dummy; } ;
typedef  enum bna_tx_event { ____Placeholder_bna_tx_event } bna_tx_event ;

/* Variables and functions */
#define  TX_E_BW_UPDATE 132 
#define  TX_E_FAIL 131 
#define  TX_E_PRIO_CHANGE 130 
#define  TX_E_START 129 
#define  TX_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_tx_sm_start_wait ; 
 int /*<<< orphan*/  call_tx_prio_change_cbfn (struct bna_tx*) ; 
 int /*<<< orphan*/  call_tx_stop_cbfn (struct bna_tx*) ; 

__attribute__((used)) static void
bna_tx_sm_stopped(struct bna_tx *tx, enum bna_tx_event event)
{
	switch (event) {
	case TX_E_START:
		bfa_fsm_set_state(tx, bna_tx_sm_start_wait);
		break;

	case TX_E_STOP:
		call_tx_stop_cbfn(tx);
		break;

	case TX_E_FAIL:
		/* No-op */
		break;

	case TX_E_PRIO_CHANGE:
		call_tx_prio_change_cbfn(tx);
		break;

	case TX_E_BW_UPDATE:
		/* No-op */
		break;

	default:
		bfa_sm_fault(event);
	}
}