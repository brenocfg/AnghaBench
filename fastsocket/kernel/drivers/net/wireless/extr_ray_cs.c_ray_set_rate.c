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
struct iw_param {int value; } ;
struct TYPE_3__ {scalar_t__ card_status; int fw_ver; int net_default_tx_rate; } ;
typedef  TYPE_1__ ray_dev_t ;

/* Variables and functions */
 scalar_t__ CARD_AWAITING_PARAM ; 
 int EBUSY ; 
 int EINVAL ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_set_rate(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_param *vwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);

	/* Reject if card is already initialised */
	if (local->card_status != CARD_AWAITING_PARAM)
		return -EBUSY;

	/* Check if rate is in range */
	if ((vwrq->value != 1000000) && (vwrq->value != 2000000))
		return -EINVAL;

	/* Hack for 1.5 Mb/s instead of 2 Mb/s */
	if ((local->fw_ver == 0x55) &&	/* Please check */
	    (vwrq->value == 2000000))
		local->net_default_tx_rate = 3;
	else
		local->net_default_tx_rate = vwrq->value / 500000;

	return 0;
}