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
struct iw_param {int flags; int /*<<< orphan*/  value; int /*<<< orphan*/  disabled; } ;
struct atmel_private {int /*<<< orphan*/  short_retry; int /*<<< orphan*/  long_retry; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_set_retry(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_param *vwrq,
			   char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);

	if (!vwrq->disabled && (vwrq->flags & IW_RETRY_LIMIT)) {
		if (vwrq->flags & IW_RETRY_LONG)
			priv->long_retry = vwrq->value;
		else if (vwrq->flags & IW_RETRY_SHORT)
			priv->short_retry = vwrq->value;
		else {
			/* No modifier : set both */
			priv->long_retry = vwrq->value;
			priv->short_retry = vwrq->value;
		}
		return -EINPROGRESS;
	}

	return -EINVAL;
}