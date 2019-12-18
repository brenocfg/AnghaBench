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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {scalar_t__ rate_driver_data; } ;
struct carl9170_tx_info {int /*<<< orphan*/  timeout; } ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 scalar_t__ carl9170_alloc_dev_space (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *carl9170_tx_pick_skb(struct ar9170 *ar,
					    struct sk_buff_head *queue)
{
	struct sk_buff *skb;
	struct ieee80211_tx_info *info;
	struct carl9170_tx_info *arinfo;

	BUILD_BUG_ON(sizeof(*arinfo) > sizeof(info->rate_driver_data));

	spin_lock_bh(&queue->lock);
	skb = skb_peek(queue);
	if (unlikely(!skb))
		goto err_unlock;

	if (carl9170_alloc_dev_space(ar, skb))
		goto err_unlock;

	__skb_unlink(skb, queue);
	spin_unlock_bh(&queue->lock);

	info = IEEE80211_SKB_CB(skb);
	arinfo = (void *) info->rate_driver_data;

	arinfo->timeout = jiffies;
	return skb;

err_unlock:
	spin_unlock_bh(&queue->lock);
	return NULL;
}