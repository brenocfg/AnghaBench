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
struct sk_buff {int dummy; } ;
struct p54_common {int /*<<< orphan*/  tx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  p54_tx_pending (struct p54_common*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void p54_tx(struct p54_common *priv, struct sk_buff *skb)
{
	skb_queue_tail(&priv->tx_pending, skb);
	p54_tx_pending(priv);
}