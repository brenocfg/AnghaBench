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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_LONGRETRIES ; 
 int /*<<< orphan*/  DOT11_OID_MAXTXLIFETIME ; 
 int /*<<< orphan*/  DOT11_OID_SHORTRETRIES ; 
 int EINVAL ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int mgt_set_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_set_retry(struct net_device *ndev, struct iw_request_info *info,
		  struct iw_param *vwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	u32 slimit = 0, llimit = 0;	/* short and long limit */
	u32 lifetime = 0;
	int rvalue = 0;

	if (vwrq->disabled)
		/* we cannot disable this feature */
		return -EINVAL;

	if (vwrq->flags & IW_RETRY_LIMIT) {
		if (vwrq->flags & IW_RETRY_SHORT)
			slimit = vwrq->value;
		else if (vwrq->flags & IW_RETRY_LONG)
			llimit = vwrq->value;
		else {
			/* we are asked to set both */
			slimit = vwrq->value;
			llimit = vwrq->value;
		}
	}
	if (vwrq->flags & IW_RETRY_LIFETIME)
		/* Wireless tools use us unit while the device uses 1024 us unit */
		lifetime = vwrq->value / 1024;

	/* now set what is requested */
	if (slimit)
		rvalue =
		    mgt_set_request(priv, DOT11_OID_SHORTRETRIES, 0, &slimit);
	if (llimit)
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_LONGRETRIES, 0, &llimit);
	if (lifetime)
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_MAXTXLIFETIME, 0,
				    &lifetime);
	return rvalue;
}