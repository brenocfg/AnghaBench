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
struct sge_txq {int /*<<< orphan*/  stops; } ;
struct sge_qset {int /*<<< orphan*/  txq_stopped; } ;
struct netdev_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXQ_ETH ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void t3_stop_tx_queue(struct netdev_queue *txq,
				    struct sge_qset *qs, struct sge_txq *q)
{
	netif_tx_stop_queue(txq);
	set_bit(TXQ_ETH, &qs->txq_stopped);
	q->stops++;
}