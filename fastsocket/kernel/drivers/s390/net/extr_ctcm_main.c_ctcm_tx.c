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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; struct ctcm_priv* ml_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct ctcm_priv {int /*<<< orphan*/ * channel; TYPE_1__ stats; int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 int /*<<< orphan*/  DEV_EVENT_START ; 
 scalar_t__ DEV_STATE_RUNNING ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ LL_HEADER_LENGTH ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 size_t WRITE ; 
 scalar_t__ ctcm_test_and_set_busy (struct net_device*) ; 
 scalar_t__ ctcm_transmit_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ fsm_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 

__attribute__((used)) static int ctcm_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct ctcm_priv *priv = dev->ml_priv;

	if (skb == NULL) {
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
				"%s(%s): NULL sk_buff passed",
					CTCM_FUNTAIL, dev->name);
		priv->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}
	if (skb_headroom(skb) < (LL_HEADER_LENGTH + 2)) {
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): Got sk_buff with head room < %ld bytes",
			CTCM_FUNTAIL, dev->name, LL_HEADER_LENGTH + 2);
		dev_kfree_skb(skb);
		priv->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	/*
	 * If channels are not running, try to restart them
	 * and throw away packet.
	 */
	if (fsm_getstate(priv->fsm) != DEV_STATE_RUNNING) {
		fsm_event(priv->fsm, DEV_EVENT_START, dev);
		dev_kfree_skb(skb);
		priv->stats.tx_dropped++;
		priv->stats.tx_errors++;
		priv->stats.tx_carrier_errors++;
		return NETDEV_TX_OK;
	}

	if (ctcm_test_and_set_busy(dev))
		return NETDEV_TX_BUSY;

	dev->trans_start = jiffies;
	if (ctcm_transmit_skb(priv->channel[WRITE], skb) != 0)
		return NETDEV_TX_BUSY;
	return NETDEV_TX_OK;
}