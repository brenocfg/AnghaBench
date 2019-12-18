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
struct bfusb_data {int /*<<< orphan*/  state; int /*<<< orphan*/  transmit_q; int /*<<< orphan*/  pending_tx; } ;

/* Variables and functions */
 scalar_t__ BFUSB_MAX_BULK_TX ; 
 int /*<<< orphan*/  BFUSB_TX_PROCESS ; 
 int /*<<< orphan*/  BFUSB_TX_WAKEUP ; 
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bfusb_send_bulk (struct bfusb_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfusb_tx_wakeup(struct bfusb_data *data)
{
	struct sk_buff *skb;

	BT_DBG("bfusb %p", data);

	if (test_and_set_bit(BFUSB_TX_PROCESS, &data->state)) {
		set_bit(BFUSB_TX_WAKEUP, &data->state);
		return;
	}

	do {
		clear_bit(BFUSB_TX_WAKEUP, &data->state);

		while ((atomic_read(&data->pending_tx) < BFUSB_MAX_BULK_TX) &&
				(skb = skb_dequeue(&data->transmit_q))) {
			if (bfusb_send_bulk(data, skb) < 0) {
				skb_queue_head(&data->transmit_q, skb);
				break;
			}
		}

	} while (test_bit(BFUSB_TX_WAKEUP, &data->state));

	clear_bit(BFUSB_TX_PROCESS, &data->state);
}