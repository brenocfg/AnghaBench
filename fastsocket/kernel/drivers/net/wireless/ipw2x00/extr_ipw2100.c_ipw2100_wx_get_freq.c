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
struct TYPE_2__ {int /*<<< orphan*/  m; scalar_t__ e; } ;
union iwreq_data {TYPE_1__ freq; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int config; int status; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int CFG_STATIC_CHANNEL ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int /*<<< orphan*/ ) ; 
 int STATUS_ASSOCIATED ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static int ipw2100_wx_get_freq(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	/*
	 * This can be called at any time.  No action lock required
	 */

	struct ipw2100_priv *priv = libipw_priv(dev);

	wrqu->freq.e = 0;

	/* If we are associated, trying to associate, or have a statically
	 * configured CHANNEL then return that; otherwise return ANY */
	if (priv->config & CFG_STATIC_CHANNEL ||
	    priv->status & STATUS_ASSOCIATED)
		wrqu->freq.m = priv->channel;
	else
		wrqu->freq.m = 0;

	IPW_DEBUG_WX("GET Freq/Channel -> %d\n", priv->channel);
	return 0;

}