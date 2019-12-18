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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct TYPE_3__ {int level; } ;
struct TYPE_4__ {TYPE_1__ qual; } ;
struct r8180_priv {int /*<<< orphan*/  wx_sem; TYPE_2__ wstats; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8180_wx_get_siglevel(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	//struct ieee80211_network *network = &(priv->ieee80211->current_network);
	int ret = 0;



	down(&priv->wx_sem);
	// Modify by hikaru 6.5
	*((int *)extra) = priv->wstats.qual.level;//for interface test ,it should be the priv->wstats.qual.level;



	up(&priv->wx_sem);

	return ret;
}