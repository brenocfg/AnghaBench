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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_hardware_context {int capabilities2; int beacon_state; } ;
struct qlcnic_adapter {int max_sds_rings; int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 scalar_t__ QLCNIC_BEACON_DISABLE ; 
 scalar_t__ QLCNIC_BEACON_EANBLE ; 
 int QLCNIC_FW_CAPABILITY_2_BEACON ; 
 int /*<<< orphan*/  QLCNIC_LED_TEST ; 
 int QL_STATUS_INVALID_PARAM ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __QLCNIC_DIAG_RES_ALLOC ; 
 int /*<<< orphan*/  __QLCNIC_LED_ENABLE ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int qlcnic_config_led (struct qlcnic_adapter*,scalar_t__,scalar_t__) ; 
 int qlcnic_diag_alloc_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_diag_free_res (int /*<<< orphan*/ ,int) ; 
 int qlcnic_get_beacon_state (struct qlcnic_adapter*,scalar_t__*) ; 
 int qlcnic_validate_beacon (struct qlcnic_adapter*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_82xx_store_beacon(struct qlcnic_adapter *adapter,
				    const char *buf, size_t len)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err, max_sds_rings = adapter->max_sds_rings;
	u16 beacon;
	u8 h_beacon_state, b_state, b_rate;

	if (len != sizeof(u16))
		return QL_STATUS_INVALID_PARAM;

	memcpy(&beacon, buf, sizeof(u16));
	err = qlcnic_validate_beacon(adapter, beacon, &b_state, &b_rate);
	if (err)
		return err;

	if ((ahw->capabilities2 & QLCNIC_FW_CAPABILITY_2_BEACON)) {
		err = qlcnic_get_beacon_state(adapter, &h_beacon_state);
		if (!err) {
			dev_info(&adapter->pdev->dev,
				 "Failed to get current beacon state\n");
		} else {
			if (h_beacon_state == QLCNIC_BEACON_DISABLE)
				ahw->beacon_state = 0;
			else if (h_beacon_state == QLCNIC_BEACON_EANBLE)
				ahw->beacon_state = 2;
		}
	}

	if (ahw->beacon_state == b_state)
		return len;

	rtnl_lock();
	if (!ahw->beacon_state) {
		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state)) {
			rtnl_unlock();
			return -EBUSY;
		}
	}

	if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
		err = -EIO;
		goto out;
	}

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		err = qlcnic_diag_alloc_res(adapter->netdev, QLCNIC_LED_TEST);
		if (err)
			goto out;
		set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
	}

	err = qlcnic_config_led(adapter, b_state, b_rate);
	if (!err) {
		err = len;
		ahw->beacon_state = b_state;
	}

	if (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_free_res(adapter->netdev, max_sds_rings);

out:
	if (!ahw->beacon_state)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);
	rtnl_unlock();

	return err;
}