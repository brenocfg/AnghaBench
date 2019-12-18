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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {scalar_t__ value; scalar_t__ disabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 scalar_t__ MRVDRV_RTS_MAX_VALUE ; 
 int /*<<< orphan*/  SNMP_MIB_OID_RTS_THRESHOLD ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int lbs_set_snmp_mib (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_set_rts(struct net_device *dev, struct iw_request_info *info,
			struct iw_param *vwrq, char *extra)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;
	u32 val = vwrq->value;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (vwrq->disabled)
		val = MRVDRV_RTS_MAX_VALUE;

	if (val > MRVDRV_RTS_MAX_VALUE) /* min rts value is 0 */
		return -EINVAL;

	ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_RTS_THRESHOLD, (u16) val);

	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}