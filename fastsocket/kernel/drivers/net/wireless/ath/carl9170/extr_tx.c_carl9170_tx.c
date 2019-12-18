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
struct ar9170 {int tx_schedule; int /*<<< orphan*/  tx_janitor; TYPE_1__* hw; int /*<<< orphan*/ * tx_status; int /*<<< orphan*/  tx_total_pending; int /*<<< orphan*/ * tx_pending; } ;
struct TYPE_2__ {unsigned int queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_TX_TIMEOUT ; 
 int /*<<< orphan*/  IS_STARTED (struct ar9170*) ; 
 unsigned int __carl9170_get_queue (struct ar9170*,unsigned int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_bar_check (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_tx_get_skb (struct sk_buff*) ; 
 struct sk_buff* carl9170_tx_pick_skb (struct ar9170*,int /*<<< orphan*/ *) ; 
 int carl9170_tx_ps_drop (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_usb_handle_tx_err (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_tx (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void carl9170_tx(struct ar9170 *ar)
{
	struct sk_buff *skb;
	unsigned int i, q;
	bool schedule_garbagecollector = false;

	ar->tx_schedule = false;

	if (unlikely(!IS_STARTED(ar)))
		return;

	carl9170_usb_handle_tx_err(ar);

	for (i = 0; i < ar->hw->queues; i++) {
		while (!skb_queue_empty(&ar->tx_pending[i])) {
			skb = carl9170_tx_pick_skb(ar, &ar->tx_pending[i]);
			if (unlikely(!skb))
				break;

			if (unlikely(carl9170_tx_ps_drop(ar, skb)))
				continue;

			carl9170_bar_check(ar, skb);

			atomic_inc(&ar->tx_total_pending);

			q = __carl9170_get_queue(ar, i);
			/*
			 * NB: tx_status[i] vs. tx_status[q],
			 * TODO: Move into pick_skb or alloc_dev_space.
			 */
			skb_queue_tail(&ar->tx_status[q], skb);

			/*
			 * increase ref count to "2".
			 * Ref counting is the easiest way to solve the
			 * race between the urb's completion routine:
			 *	carl9170_tx_callback
			 * and wlan tx status functions:
			 *	carl9170_tx_status/janitor.
			 */
			carl9170_tx_get_skb(skb);

			carl9170_usb_tx(ar, skb);
			schedule_garbagecollector = true;
		}
	}

	if (!schedule_garbagecollector)
		return;

	ieee80211_queue_delayed_work(ar->hw, &ar->tx_janitor,
		msecs_to_jiffies(CARL9170_TX_TIMEOUT));
}