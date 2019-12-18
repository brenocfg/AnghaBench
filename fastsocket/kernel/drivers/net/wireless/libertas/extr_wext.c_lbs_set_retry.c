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
typedef  scalar_t__ u16 ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ txretrycount; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; scalar_t__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  SNMP_MIB_OID_LONG_RETRY_LIMIT ; 
 int /*<<< orphan*/  SNMP_MIB_OID_SHORT_RETRY_LIMIT ; 
 scalar_t__ TX_RETRY_MAX ; 
 scalar_t__ TX_RETRY_MIN ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int lbs_set_snmp_mib (struct lbs_private*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lbs_set_retry(struct net_device *dev, struct iw_request_info *info,
			  struct iw_param *vwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;
	int ret = 0;
	u16 slimit = 0, llimit = 0;

	lbs_deb_enter(LBS_DEB_WEXT);

        if ((vwrq->flags & IW_RETRY_TYPE) != IW_RETRY_LIMIT)
                return -EOPNOTSUPP;

	/* The MAC has a 4-bit Total_Tx_Count register
	   Total_Tx_Count = 1 + Tx_Retry_Count */
#define TX_RETRY_MIN 0
#define TX_RETRY_MAX 14
	if (vwrq->value < TX_RETRY_MIN || vwrq->value > TX_RETRY_MAX)
		return -EINVAL;

	/* Add 1 to convert retry count to try count */
	if (vwrq->flags & IW_RETRY_SHORT)
		slimit = (u16) (vwrq->value + 1);
	else if (vwrq->flags & IW_RETRY_LONG)
		llimit = (u16) (vwrq->value + 1);
	else
		slimit = llimit = (u16) (vwrq->value + 1); /* set both */

	if (llimit) {
		ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_LONG_RETRY_LIMIT,
				       llimit);
		if (ret)
			goto out;
	}

	if (slimit) {
		/* txretrycount follows the short retry limit */
		priv->txretrycount = slimit;
		ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_SHORT_RETRY_LIMIT,
				       slimit);
		if (ret)
			goto out;
	}

out:
	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}