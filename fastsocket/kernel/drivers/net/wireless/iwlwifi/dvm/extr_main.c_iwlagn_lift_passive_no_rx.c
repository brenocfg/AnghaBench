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
struct iwl_priv {int passive_no_rx; int /*<<< orphan*/  hw; int /*<<< orphan*/  transport_queue_stop; } ;

/* Variables and functions */
 int IWLAGN_FIRST_AMPDU_QUEUE ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_priv*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

void iwlagn_lift_passive_no_rx(struct iwl_priv *priv)
{
	int mq;

	if (!priv->passive_no_rx)
		return;

	for (mq = 0; mq < IWLAGN_FIRST_AMPDU_QUEUE; mq++) {
		if (!test_bit(mq, &priv->transport_queue_stop)) {
			IWL_DEBUG_TX_QUEUES(priv, "Wake queue %d", mq);
			ieee80211_wake_queue(priv->hw, mq);
		} else {
			IWL_DEBUG_TX_QUEUES(priv, "Don't wake queue %d", mq);
		}
	}

	priv->passive_no_rx = false;
}