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
struct aoedev {int /*<<< orphan*/  skbpool; } ;
struct TYPE_2__ {int /*<<< orphan*/  dataref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ZLEN ; 
 scalar_t__ NSKBPOOLMAX ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct sk_buff* new_skb (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
skb_pool_get(struct aoedev *d)
{
	struct sk_buff *skb = skb_peek(&d->skbpool);

	if (skb && atomic_read(&skb_shinfo(skb)->dataref) == 1) {
		__skb_unlink(skb, &d->skbpool);
		return skb;
	}
	if (skb_queue_len(&d->skbpool) < NSKBPOOLMAX &&
	    (skb = new_skb(ETH_ZLEN)))
		return skb;

	return NULL;
}