#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {unsigned char const* bssid; int /*<<< orphan*/  mutex; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  CFG_STATIC_BSSID ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_ASSOC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int /*<<< orphan*/  ipw_associate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_disassociate (struct ipw_priv*) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_wap(struct net_device *dev,
			  struct iw_request_info *info,
			  union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);

	static const unsigned char any[] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
	static const unsigned char off[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	if (wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		return -EINVAL;
	mutex_lock(&priv->mutex);
	if (!memcmp(any, wrqu->ap_addr.sa_data, ETH_ALEN) ||
	    !memcmp(off, wrqu->ap_addr.sa_data, ETH_ALEN)) {
		/* we disable mandatory BSSID association */
		IPW_DEBUG_WX("Setting AP BSSID to ANY\n");
		priv->config &= ~CFG_STATIC_BSSID;
		IPW_DEBUG_ASSOC("Attempting to associate with new "
				"parameters.\n");
		ipw_associate(priv);
		mutex_unlock(&priv->mutex);
		return 0;
	}

	priv->config |= CFG_STATIC_BSSID;
	if (!memcmp(priv->bssid, wrqu->ap_addr.sa_data, ETH_ALEN)) {
		IPW_DEBUG_WX("BSSID set to current BSSID.\n");
		mutex_unlock(&priv->mutex);
		return 0;
	}

	IPW_DEBUG_WX("Setting mandatory BSSID to %pM\n",
		     wrqu->ap_addr.sa_data);

	memcpy(priv->bssid, wrqu->ap_addr.sa_data, ETH_ALEN);

	/* Network configuration changed -- force [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to BSSID change.\n");
	if (!ipw_disassociate(priv))
		ipw_associate(priv);

	mutex_unlock(&priv->mutex);
	return 0;
}