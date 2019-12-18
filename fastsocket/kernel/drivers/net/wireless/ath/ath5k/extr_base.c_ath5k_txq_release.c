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
struct ath5k_txq {int setup; int /*<<< orphan*/  qnum; } ;
struct ath5k_hw {struct ath5k_txq* txqs; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ath5k_txq*) ; 
 int /*<<< orphan*/  ath5k_hw_release_tx_queue (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_txq_release(struct ath5k_hw *ah)
{
	struct ath5k_txq *txq = ah->txqs;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(ah->txqs); i++, txq++)
		if (txq->setup) {
			ath5k_hw_release_tx_queue(ah, txq->qnum);
			txq->setup = false;
		}
}