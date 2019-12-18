#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct lbs_private {int monitormode; scalar_t__ mode; int /*<<< orphan*/ * currenttxskb; TYPE_1__ curbssparams; scalar_t__ mesh_open; scalar_t__ infra_open; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {struct lbs_private* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_MONITOR_MODE ; 
 int /*<<< orphan*/  CMD_ACT_SET ; 
 int /*<<< orphan*/  CMD_OPTION_WAITFORRSP ; 
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_add_rtap (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_adhoc_stop (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_cmd_80211_deauthenticate (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_host_to_card_done (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_prepare_and_send_command (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lbs_remove_rtap (struct lbs_private*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_2__* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t lbs_rtap_set(struct device *dev,
		struct device_attribute *attr, const char * buf, size_t count)
{
	int monitor_mode;
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;

	sscanf(buf, "%x", &monitor_mode);
	if (monitor_mode) {
		if (priv->monitormode == monitor_mode)
			return strlen(buf);
		if (!priv->monitormode) {
			if (priv->infra_open || priv->mesh_open)
				return -EBUSY;
			if (priv->mode == IW_MODE_INFRA)
				lbs_cmd_80211_deauthenticate(priv,
							     priv->curbssparams.bssid,
							     WLAN_REASON_DEAUTH_LEAVING);
			else if (priv->mode == IW_MODE_ADHOC)
				lbs_adhoc_stop(priv);
			lbs_add_rtap(priv);
		}
		priv->monitormode = monitor_mode;
	} else {
		if (!priv->monitormode)
			return strlen(buf);
		priv->monitormode = 0;
		lbs_remove_rtap(priv);

		if (priv->currenttxskb) {
			dev_kfree_skb_any(priv->currenttxskb);
			priv->currenttxskb = NULL;
		}

		/* Wake queues, command thread, etc. */
		lbs_host_to_card_done(priv);
	}

	lbs_prepare_and_send_command(priv,
			CMD_802_11_MONITOR_MODE, CMD_ACT_SET,
			CMD_OPTION_WAITFORRSP, 0, &priv->monitormode);
	return strlen(buf);
}