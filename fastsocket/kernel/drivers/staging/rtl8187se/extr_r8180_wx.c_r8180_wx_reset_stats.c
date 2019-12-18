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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct TYPE_2__ {scalar_t__ rxicverr; scalar_t__ rxcrcerrmax; scalar_t__ rxcrcerrmid; scalar_t__ rxcrcerrmin; scalar_t__ txretry; scalar_t__ txlperr; scalar_t__ txlpokint; scalar_t__ txbeaconerr; scalar_t__ txbeacon; scalar_t__ rxdmafail; scalar_t__ txoverflow; scalar_t__ shints; scalar_t__ ints; scalar_t__ txhperr; scalar_t__ txhpokint; scalar_t__ txnpokint; scalar_t__ rxint; scalar_t__ rxoverflow; scalar_t__ rxerr; scalar_t__ txresumed; scalar_t__ txnperr; scalar_t__ rxnopointer; scalar_t__ rxnodata; scalar_t__ rxnolast; scalar_t__ rxrdu; scalar_t__ txrdu; } ;
struct r8180_priv {int /*<<< orphan*/  wx_sem; TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8180_wx_reset_stats(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct r8180_priv *priv =ieee80211_priv(dev);
	down(&priv->wx_sem);

	priv->stats.txrdu = 0;
	priv->stats.rxrdu = 0;
	priv->stats.rxnolast = 0;
	priv->stats.rxnodata = 0;
	priv->stats.rxnopointer = 0;
	priv->stats.txnperr = 0;
	priv->stats.txresumed = 0;
	priv->stats.rxerr = 0;
	priv->stats.rxoverflow = 0;
	priv->stats.rxint = 0;

	priv->stats.txnpokint = 0;
	priv->stats.txhpokint = 0;
	priv->stats.txhperr = 0;
	priv->stats.ints = 0;
	priv->stats.shints = 0;
	priv->stats.txoverflow = 0;
	priv->stats.rxdmafail = 0;
	priv->stats.txbeacon = 0;
	priv->stats.txbeaconerr = 0;
	priv->stats.txlpokint = 0;
	priv->stats.txlperr = 0;
	priv->stats.txretry =0;//20060601
	priv->stats.rxcrcerrmin=0;
	priv->stats.rxcrcerrmid=0;
	priv->stats.rxcrcerrmax=0;
	priv->stats.rxicverr=0;

	up(&priv->wx_sem);

	return 0;

}