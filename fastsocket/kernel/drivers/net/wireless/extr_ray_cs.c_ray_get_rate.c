#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; scalar_t__ fixed; } ;
struct TYPE_3__ {int net_default_tx_rate; } ;
typedef  TYPE_1__ ray_dev_t ;

/* Variables and functions */
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_get_rate(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_param *vwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);

	if (local->net_default_tx_rate == 3)
		vwrq->value = 2000000;	/* Hum... */
	else
		vwrq->value = local->net_default_tx_rate * 500000;
	vwrq->fixed = 0;	/* We are in auto mode */

	return 0;
}