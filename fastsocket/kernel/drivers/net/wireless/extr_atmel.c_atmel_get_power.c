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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int disabled; int /*<<< orphan*/  flags; } ;
struct atmel_private {scalar_t__ power_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_POWER_ON ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_power(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_param *vwrq,
			   char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	vwrq->disabled = priv->power_mode ? 0 : 1;
	vwrq->flags = IW_POWER_ON;
	return 0;
}