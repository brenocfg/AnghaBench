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
struct ixgb_adapter {int /*<<< orphan*/  blink_timer; int /*<<< orphan*/  hw; int /*<<< orphan*/  led_status; } ;

/* Variables and functions */
 scalar_t__ IXGB_ID_INTERVAL ; 
 int /*<<< orphan*/  IXGB_LED_ON ; 
 int /*<<< orphan*/  ixgb_led_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgb_led_on (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ test_and_change_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ixgb_led_blink_callback(unsigned long data)
{
	struct ixgb_adapter *adapter = (struct ixgb_adapter *)data;

	if (test_and_change_bit(IXGB_LED_ON, &adapter->led_status))
		ixgb_led_off(&adapter->hw);
	else
		ixgb_led_on(&adapter->hw);

	mod_timer(&adapter->blink_timer, jiffies + IXGB_ID_INTERVAL);
}