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
struct TYPE_2__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int config; int status; int /*<<< orphan*/  mutex; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int CFG_STATIC_BSSID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int /*<<< orphan*/ ) ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_ASSOCIATING ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_get_wap(struct net_device *dev,
			  struct iw_request_info *info,
			  union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);

	/* If we are associated, trying to associate, or have a statically
	 * configured BSSID then return that; otherwise return ANY */
	mutex_lock(&priv->mutex);
	if (priv->config & CFG_STATIC_BSSID ||
	    priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)) {
		wrqu->ap_addr.sa_family = ARPHRD_ETHER;
		memcpy(wrqu->ap_addr.sa_data, priv->bssid, ETH_ALEN);
	} else
		memset(wrqu->ap_addr.sa_data, 0, ETH_ALEN);

	IPW_DEBUG_WX("Getting WAP BSSID: %pM\n",
		     wrqu->ap_addr.sa_data);
	mutex_unlock(&priv->mutex);
	return 0;
}