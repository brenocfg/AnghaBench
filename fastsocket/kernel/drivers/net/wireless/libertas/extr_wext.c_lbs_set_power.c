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
struct lbs_private {int fwcapinfo; scalar_t__ psmode; scalar_t__ psstate; scalar_t__ connect_status; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; scalar_t__ disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_OPTION_WAITFORRSP ; 
 int EINVAL ; 
 int FW_CAPINFO_PS ; 
 int IW_POWER_PERIOD ; 
 int IW_POWER_TIMEOUT ; 
 int IW_POWER_TYPE ; 
 scalar_t__ LBS802_11POWERMODECAM ; 
 scalar_t__ LBS802_11POWERMODEMAX_PSP ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*) ; 
 int /*<<< orphan*/  lbs_ps_sleep (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_ps_wakeup (struct lbs_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_set_power(struct net_device *dev, struct iw_request_info *info,
			  struct iw_param *vwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	if (!(priv->fwcapinfo & FW_CAPINFO_PS)) {
		if (vwrq->disabled)
			return 0;
		else
			return -EINVAL;
	}

	/* PS is currently supported only in Infrastructure mode
	 * Remove this check if it is to be supported in IBSS mode also
	 */

	if (vwrq->disabled) {
		priv->psmode = LBS802_11POWERMODECAM;
		if (priv->psstate != PS_STATE_FULL_POWER) {
			lbs_ps_wakeup(priv, CMD_OPTION_WAITFORRSP);
		}

		return 0;
	}

	if ((vwrq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) {
		lbs_deb_wext(
		       "setting power timeout is not supported\n");
		return -EINVAL;
	} else if ((vwrq->flags & IW_POWER_TYPE) == IW_POWER_PERIOD) {
		lbs_deb_wext("setting power period not supported\n");
		return -EINVAL;
	}

	if (priv->psmode != LBS802_11POWERMODECAM) {
		return 0;
	}

	priv->psmode = LBS802_11POWERMODEMAX_PSP;

	if (priv->connect_status == LBS_CONNECTED) {
		lbs_ps_sleep(priv, CMD_OPTION_WAITFORRSP);
	}

	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}