#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct il_queue {scalar_t__ read_ptr; scalar_t__ write_ptr; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int max_txq_num; } ;
struct il_priv {int cmd_queue; int /*<<< orphan*/  mutex; TYPE_2__* txq; TYPE_1__ hw_params; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
struct TYPE_4__ {struct il_queue q; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

void il_mac_flush(struct ieee80211_hw *hw, u32 queues, bool drop)
{
	struct il_priv *il = hw->priv;
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	int i;

	mutex_lock(&il->mutex);
	D_MAC80211("enter\n");

	if (il->txq == NULL)
		goto out;

	for (i = 0; i < il->hw_params.max_txq_num; i++) {
		struct il_queue *q;

		if (i == il->cmd_queue)
			continue;

		q = &il->txq[i].q;
		if (q->read_ptr == q->write_ptr)
			continue;

		if (time_after(jiffies, timeout)) {
			IL_ERR("Failed to flush queue %d\n", q->id);
			break;
		}

		msleep(20);
	}
out:
	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
}