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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct bnad {struct net_device* netdev; } ;
struct bna_tcb {int /*<<< orphan*/  flags; int /*<<< orphan*/  i_dbell; int /*<<< orphan*/  q_depth; } ;

/* Variables and functions */
 scalar_t__ BNAD_NETIF_WAKE_THRESHOLD ; 
 int /*<<< orphan*/  BNAD_TXQ_FREE_SENT ; 
 int /*<<< orphan*/  BNAD_TXQ_TX_STARTED ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 scalar_t__ BNA_QE_FREE_CNT (struct bna_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ib_ack (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bnad_txcmpl_process (struct bnad*,struct bna_tcb*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (scalar_t__) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_wakeup ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
bnad_tx_complete(struct bnad *bnad, struct bna_tcb *tcb)
{
	struct net_device *netdev = bnad->netdev;
	u32 sent = 0;

	if (test_and_set_bit(BNAD_TXQ_FREE_SENT, &tcb->flags))
		return 0;

	sent = bnad_txcmpl_process(bnad, tcb);
	if (sent) {
		if (netif_queue_stopped(netdev) &&
		    netif_carrier_ok(netdev) &&
		    BNA_QE_FREE_CNT(tcb, tcb->q_depth) >=
				    BNAD_NETIF_WAKE_THRESHOLD) {
			if (test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)) {
				netif_wake_queue(netdev);
				BNAD_UPDATE_CTR(bnad, netif_queue_wakeup);
			}
		}
	}

	if (likely(test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)))
		bna_ib_ack(tcb->i_dbell, sent);

	smp_mb__before_clear_bit();
	clear_bit(BNAD_TXQ_FREE_SENT, &tcb->flags);

	return sent;
}