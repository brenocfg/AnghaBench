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
typedef  int u8 ;
struct il_tx_queue {int swq_id; } ;
struct il_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/ * queue_stop_count; int /*<<< orphan*/  queue_stopped; } ;

/* Variables and functions */
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
il_stop_queue(struct il_priv *il, struct il_tx_queue *txq)
{
	u8 queue = txq->swq_id;
	u8 ac = queue & 3;
	u8 hwq = (queue >> 2) & 0x1f;

	if (!test_and_set_bit(hwq, il->queue_stopped))
		if (atomic_inc_return(&il->queue_stop_count[ac]) > 0)
			ieee80211_stop_queue(il->hw, ac);
}