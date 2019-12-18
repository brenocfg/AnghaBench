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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  led_status; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_LED_ON ; 
 unsigned long UINT_MAX ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_blink_led (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_cleanup_led (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_led_off (struct e1000_hw*) ; 
 int /*<<< orphan*/  msleep_interruptible (unsigned long) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_phys_id(struct net_device *netdev, u32 data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	unsigned long timeout;

	timeout = data * 1000;

	/*
	 *  msleep_interruptable only accepts unsigned int so we are limited
	 * in how long a duration we can wait
	 */
	if (!timeout || timeout > UINT_MAX)
		timeout = UINT_MAX;

	igb_blink_led(hw);
	msleep_interruptible(timeout);

	igb_led_off(hw);
	clear_bit(IGB_LED_ON, &adapter->led_status);
	igb_cleanup_led(hw);

	return 0;
}