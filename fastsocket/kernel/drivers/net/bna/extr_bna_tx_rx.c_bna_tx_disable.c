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
struct bna_tx {void (* stop_cbfn ) (void*,struct bna_tx*) ;void* stop_cbarg; int /*<<< orphan*/  flags; TYPE_1__* bna; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_2__ {void* bnad; } ;

/* Variables and functions */
 int BNA_SOFT_CLEANUP ; 
 int /*<<< orphan*/  BNA_TX_F_ENABLED ; 
 int /*<<< orphan*/  TX_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_tx*,int /*<<< orphan*/ ) ; 
 void stub1 (void*,struct bna_tx*) ; 

void
bna_tx_disable(struct bna_tx *tx, enum bna_cleanup_type type,
		void (*cbfn)(void *, struct bna_tx *))
{
	if (type == BNA_SOFT_CLEANUP) {
		(*cbfn)(tx->bna->bnad, tx);
		return;
	}

	tx->stop_cbfn = cbfn;
	tx->stop_cbarg = tx->bna->bnad;

	tx->flags &= ~BNA_TX_F_ENABLED;

	bfa_fsm_send_event(tx, TX_E_STOP);
}