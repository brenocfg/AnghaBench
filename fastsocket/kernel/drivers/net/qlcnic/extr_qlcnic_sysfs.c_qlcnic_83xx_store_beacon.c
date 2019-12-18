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
struct qlcnic_hardware_context {unsigned long beacon_state; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  __QLCNIC_LED_ENABLE ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qlcnic_83xx_config_led (struct qlcnic_adapter*,int,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_83xx_store_beacon(struct qlcnic_adapter *adapter,
				    const char *buf, size_t len)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	unsigned long h_beacon;
	int err;

	if (test_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EIO;

	if (strict_strtoul(buf, 2, &h_beacon))
		return -EINVAL;

	if (ahw->beacon_state == h_beacon)
		return len;

	rtnl_lock();
	if (!ahw->beacon_state) {
		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state)) {
			rtnl_unlock();
			return -EBUSY;
		}
	}

	if (h_beacon)
		err = qlcnic_83xx_config_led(adapter, 1, h_beacon);
	else
		err = qlcnic_83xx_config_led(adapter, 0, !h_beacon);
	if (!err)
		ahw->beacon_state = h_beacon;

	if (!ahw->beacon_state)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	rtnl_unlock();
	return len;
}