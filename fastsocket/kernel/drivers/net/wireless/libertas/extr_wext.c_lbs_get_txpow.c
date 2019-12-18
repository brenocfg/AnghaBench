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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {void* txpower_cur; int /*<<< orphan*/  radio_on; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int disabled; int fixed; int /*<<< orphan*/  flags; void* value; } ;
typedef  void* s16 ;

/* Variables and functions */
 int /*<<< orphan*/  IW_TXPOW_DBM ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,...) ; 
 int lbs_get_tx_power (struct lbs_private*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_get_txpow(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_param *vwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;
	s16 curlevel = 0;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (!priv->radio_on) {
		lbs_deb_wext("tx power off\n");
		vwrq->value = 0;
		vwrq->disabled = 1;
		goto out;
	}

	ret = lbs_get_tx_power(priv, &curlevel, NULL, NULL);
	if (ret)
		goto out;

	lbs_deb_wext("tx power level %d dbm\n", curlevel);
	priv->txpower_cur = curlevel;

	vwrq->value = curlevel;
	vwrq->fixed = 1;
	vwrq->disabled = 0;
	vwrq->flags = IW_TXPOW_DBM;

out:
	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}