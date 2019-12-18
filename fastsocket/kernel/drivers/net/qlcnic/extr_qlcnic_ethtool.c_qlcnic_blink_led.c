#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_adapter {int num_sds_rings; int /*<<< orphan*/  state; TYPE_3__* pdev; TYPE_2__* nic_ops; TYPE_1__* ahw; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int (* config_led ) (struct qlcnic_adapter*,int,int) ;} ;
struct TYPE_4__ {scalar_t__ op_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QLCNIC_LED_TEST ; 
 scalar_t__ QLCNIC_NON_PRIV_FUNC ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __QLCNIC_DIAG_RES_ALLOC ; 
 int /*<<< orphan*/  __QLCNIC_LED_ENABLE ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_config_led (struct qlcnic_adapter*,int,int /*<<< orphan*/ ) ; 
 int qlcnic_diag_alloc_res (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_diag_free_res (struct net_device*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct qlcnic_adapter*,int,int) ; 
 int stub2 (struct qlcnic_adapter*,int,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_blink_led(struct net_device *dev, u32 val)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	int max_sds_rings = adapter->num_sds_rings;
	int ret = 0;

	if (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) {
		netdev_warn(dev,
			"LED test not supported for non privilege function\n");
		return -EOPNOTSUPP;
	}

	if (qlcnic_83xx_check(adapter) &&
	    !test_bit(__QLCNIC_RESETTING, &adapter->state)) {

		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state))
			return -EBUSY;

		ret = qlcnic_83xx_config_led(adapter, 1, 0);
		if (ret)
			goto led_err;

		msleep_interruptible(val * 1000);

		ret = qlcnic_83xx_config_led(adapter, 0, 0);
led_err:
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);
		return ret;
	}

	if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state))
		return -EBUSY;

	if (test_bit(__QLCNIC_RESETTING, &adapter->state))
		goto done;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		ret = qlcnic_diag_alloc_res(dev, QLCNIC_LED_TEST);
		if (ret)
			goto done;
		set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
	}

	ret = adapter->nic_ops->config_led(adapter, 1, 0xf);
	if (ret) {
		dev_err(&adapter->pdev->dev,
			"Failed to set LED blink state.\n");
		goto done;
	}

	if (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_free_res(dev, max_sds_rings);

	msleep_interruptible(val * 1000);

	if (test_bit(__QLCNIC_RESETTING, &adapter->state))
		goto done;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		ret = qlcnic_diag_alloc_res(dev, QLCNIC_LED_TEST);
		if (ret)
			goto done;
		set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
	}

	ret = adapter->nic_ops->config_led(adapter, 0, 0xf);
	if (ret)
		dev_err(&adapter->pdev->dev,
			"Failed to reset LED blink state.\n");

done:
	if (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_free_res(dev, max_sds_rings);

	clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);
	return ret;

}