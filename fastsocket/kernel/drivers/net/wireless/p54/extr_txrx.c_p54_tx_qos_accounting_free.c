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
struct p54_common {scalar_t__ beacon_req_id; int /*<<< orphan*/  beacon_comp; int /*<<< orphan*/  tx_stats_lock; TYPE_1__* tx_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 size_t GET_HW_QUEUE (struct sk_buff*) ; 
 scalar_t__ GET_REQ_ID (struct sk_buff*) ; 
 scalar_t__ IS_DATA_FRAME (struct sk_buff*) ; 
 size_t P54_QUEUE_BEACON ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_wake_queues (struct p54_common*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void p54_tx_qos_accounting_free(struct p54_common *priv,
				       struct sk_buff *skb)
{
	if (IS_DATA_FRAME(skb)) {
		unsigned long flags;

		spin_lock_irqsave(&priv->tx_stats_lock, flags);
		priv->tx_stats[GET_HW_QUEUE(skb)].len--;
		spin_unlock_irqrestore(&priv->tx_stats_lock, flags);

		if (unlikely(GET_HW_QUEUE(skb) == P54_QUEUE_BEACON)) {
			if (priv->beacon_req_id == GET_REQ_ID(skb)) {
				/* this is the  active beacon set anymore */
				priv->beacon_req_id = 0;
			}
			complete(&priv->beacon_comp);
		}
	}
	p54_wake_queues(priv);
}