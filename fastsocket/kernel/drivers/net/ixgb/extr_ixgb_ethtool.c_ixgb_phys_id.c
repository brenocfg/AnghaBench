#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {unsigned long data; scalar_t__ function; } ;
struct ixgb_adapter {int /*<<< orphan*/  led_status; int /*<<< orphan*/  hw; TYPE_1__ blink_timer; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  IXGB_LED_ON ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ ixgb_led_blink_callback ; 
 int /*<<< orphan*/  ixgb_led_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ixgb_phys_id(struct net_device *netdev, u32 data)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	if (!data)
		data = INT_MAX;

	if (!adapter->blink_timer.function) {
		init_timer(&adapter->blink_timer);
		adapter->blink_timer.function = ixgb_led_blink_callback;
		adapter->blink_timer.data = (unsigned long)adapter;
	}

	mod_timer(&adapter->blink_timer, jiffies);

	msleep_interruptible(data * 1000);
	del_timer_sync(&adapter->blink_timer);
	ixgb_led_off(&adapter->hw);
	clear_bit(IXGB_LED_ON, &adapter->led_status);

	return 0;
}