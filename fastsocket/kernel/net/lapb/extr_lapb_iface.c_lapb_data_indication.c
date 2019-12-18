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
struct TYPE_2__ {int (* data_indication ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct lapb_cb {int /*<<< orphan*/  dev; TYPE_1__ callbacks; } ;

/* Variables and functions */
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

int lapb_data_indication(struct lapb_cb *lapb, struct sk_buff *skb)
{
	if (lapb->callbacks.data_indication)
		return lapb->callbacks.data_indication(lapb->dev, skb);

	kfree_skb(skb);
	return NET_RX_SUCCESS; /* For now; must be != NET_RX_DROP */
}