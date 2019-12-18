#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int e; int m; } ;
union iwreq_data {TYPE_4__ freq; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int config; int status; int /*<<< orphan*/  channel; int /*<<< orphan*/  mutex; TYPE_5__* ieee; } ;
struct TYPE_9__ {TYPE_2__* bg; TYPE_1__* a; } ;
struct TYPE_11__ {TYPE_3__ geo; } ;
struct TYPE_8__ {int freq; } ;
struct TYPE_7__ {int freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CFG_STATIC_CHANNEL ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int /*<<< orphan*/ ) ; 
#define  LIBIPW_24GHZ_BAND 129 
#define  LIBIPW_52GHZ_BAND 128 
 int STATUS_ASSOCIATED ; 
 int STATUS_ASSOCIATING ; 
 int libipw_channel_to_index (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int libipw_is_valid_channel (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_get_freq(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);

	wrqu->freq.e = 0;

	/* If we are associated, trying to associate, or have a statically
	 * configured CHANNEL then return that; otherwise return ANY */
	mutex_lock(&priv->mutex);
	if (priv->config & CFG_STATIC_CHANNEL ||
	    priv->status & (STATUS_ASSOCIATING | STATUS_ASSOCIATED)) {
		int i;

		i = libipw_channel_to_index(priv->ieee, priv->channel);
		BUG_ON(i == -1);
		wrqu->freq.e = 1;

		switch (libipw_is_valid_channel(priv->ieee, priv->channel)) {
		case LIBIPW_52GHZ_BAND:
			wrqu->freq.m = priv->ieee->geo.a[i].freq * 100000;
			break;

		case LIBIPW_24GHZ_BAND:
			wrqu->freq.m = priv->ieee->geo.bg[i].freq * 100000;
			break;

		default:
			BUG();
		}
	} else
		wrqu->freq.m = 0;

	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("GET Freq/Channel -> %d\n", priv->channel);
	return 0;
}