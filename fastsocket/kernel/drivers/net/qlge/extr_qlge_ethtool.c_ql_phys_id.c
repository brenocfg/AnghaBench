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
struct ql_adapter {int led_config; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int QL_LED_BLINK ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int ql_mb_get_led_cfg (struct ql_adapter*) ; 
 int ql_mb_set_led_cfg (struct ql_adapter*,int) ; 

__attribute__((used)) static int ql_phys_id(struct net_device *ndev, u32 data)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	u32 led_reg, i;
	int status;

	/* Save the current LED settings */
	status = ql_mb_get_led_cfg(qdev);
	if (status)
		return status;
	led_reg = qdev->led_config;

	/* Start blinking the led */
	if (!data || data > 300)
		data = 300;

	for (i = 0; i < (data * 10); i++)
		ql_mb_set_led_cfg(qdev, QL_LED_BLINK);

	/* Restore LED settings */
	status = ql_mb_set_led_cfg(qdev, led_reg);
	if (status)
		return status;

	return 0;
}