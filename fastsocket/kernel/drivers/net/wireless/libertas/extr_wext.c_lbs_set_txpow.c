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
struct lbs_private {int fwrelease; scalar_t__ txpower_max; scalar_t__ txpower_min; int /*<<< orphan*/  radio_on; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {scalar_t__ fixed; int flags; scalar_t__ disabled; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_TXPOW_DBM ; 
 int IW_TXPOW_TYPE ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  POW_ADAPT_DEFAULT_P0 ; 
 int /*<<< orphan*/  POW_ADAPT_DEFAULT_P1 ; 
 int /*<<< orphan*/  POW_ADAPT_DEFAULT_P2 ; 
 int /*<<< orphan*/  RADIO_PREAMBLE_AUTO ; 
 int /*<<< orphan*/  TPC_DEFAULT_P0 ; 
 int /*<<< orphan*/  TPC_DEFAULT_P1 ; 
 int /*<<< orphan*/  TPC_DEFAULT_P2 ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,scalar_t__) ; 
 int lbs_set_power_adapt_cfg (struct lbs_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lbs_set_radio (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int lbs_set_tpc_cfg (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lbs_set_tx_power (struct lbs_private*,scalar_t__) ; 

__attribute__((used)) static int lbs_set_txpow(struct net_device *dev, struct iw_request_info *info,
		   struct iw_param *vwrq, char *extra)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;
	s16 dbm = (s16) vwrq->value;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (vwrq->disabled) {
		lbs_set_radio(priv, RADIO_PREAMBLE_AUTO, 0);
		goto out;
	}

	if (vwrq->fixed == 0) {
		/* User requests automatic tx power control, however there are
		 * many auto tx settings.  For now use firmware defaults until
		 * we come up with a good way to expose these to the user. */
		if (priv->fwrelease < 0x09000000) {
			ret = lbs_set_power_adapt_cfg(priv, 1,
					POW_ADAPT_DEFAULT_P0,
					POW_ADAPT_DEFAULT_P1,
					POW_ADAPT_DEFAULT_P2);
			if (ret)
				goto out;
		}
		ret = lbs_set_tpc_cfg(priv, 0, TPC_DEFAULT_P0, TPC_DEFAULT_P1,
				TPC_DEFAULT_P2, 1);
		if (ret)
			goto out;
		dbm = priv->txpower_max;
	} else {
		/* Userspace check in iwrange if it should use dBm or mW,
		 * therefore this should never happen... Jean II */
		if ((vwrq->flags & IW_TXPOW_TYPE) != IW_TXPOW_DBM) {
			ret = -EOPNOTSUPP;
			goto out;
		}

		/* Validate requested power level against firmware allowed
		 * levels */
		if (priv->txpower_min && (dbm < priv->txpower_min)) {
			ret = -EINVAL;
			goto out;
		}

		if (priv->txpower_max && (dbm > priv->txpower_max)) {
			ret = -EINVAL;
			goto out;
		}
		if (priv->fwrelease < 0x09000000) {
			ret = lbs_set_power_adapt_cfg(priv, 0,
					POW_ADAPT_DEFAULT_P0,
					POW_ADAPT_DEFAULT_P1,
					POW_ADAPT_DEFAULT_P2);
			if (ret)
				goto out;
		}
		ret = lbs_set_tpc_cfg(priv, 0, TPC_DEFAULT_P0, TPC_DEFAULT_P1,
				TPC_DEFAULT_P2, 1);
		if (ret)
			goto out;
	}

	/* If the radio was off, turn it on */
	if (!priv->radio_on) {
		ret = lbs_set_radio(priv, RADIO_PREAMBLE_AUTO, 1);
		if (ret)
			goto out;
	}

	lbs_deb_wext("txpower set %d dBm\n", dbm);

	ret = lbs_set_tx_power(priv, dbm);

out:
	lbs_deb_leave_args(LBS_DEB_WEXT, "ret %d", ret);
	return ret;
}