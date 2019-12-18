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
struct sk_buff_head {int dummy; } ;
struct zd_chip {int dummy; } ;
struct zd_mac {int /*<<< orphan*/  flags; struct sk_buff_head ack_wait_queue; struct zd_chip chip; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_DEVICE_RUNNING ; 
 int /*<<< orphan*/  beacon_disable (struct zd_mac*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  housekeeping_disable (struct zd_mac*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  zd_chip_disable_hwint (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_chip_disable_int (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_chip_disable_rxtx (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_chip_switch_radio_off (struct zd_chip*) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  zd_workqueue ; 

void zd_op_stop(struct ieee80211_hw *hw)
{
	struct zd_mac *mac = zd_hw_mac(hw);
	struct zd_chip *chip = &mac->chip;
	struct sk_buff *skb;
	struct sk_buff_head *ack_wait_queue = &mac->ack_wait_queue;

	clear_bit(ZD_DEVICE_RUNNING, &mac->flags);

	/* The order here deliberately is a little different from the open()
	 * method, since we need to make sure there is no opportunity for RX
	 * frames to be processed by mac80211 after we have stopped it.
	 */

	zd_chip_disable_rxtx(chip);
	beacon_disable(mac);
	housekeeping_disable(mac);
	flush_workqueue(zd_workqueue);

	zd_chip_disable_hwint(chip);
	zd_chip_switch_radio_off(chip);
	zd_chip_disable_int(chip);


	while ((skb = skb_dequeue(ack_wait_queue)))
		dev_kfree_skb_any(skb);
}