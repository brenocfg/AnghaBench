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
union iwreq_data {int /*<<< orphan*/  param; } ;
struct r8192_priv {int /*<<< orphan*/  wx_sem; int /*<<< orphan*/  ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int ieee80211_wx_set_auth (int /*<<< orphan*/ ,struct iw_request_info*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8192_wx_set_auth(struct net_device *dev,
                                        struct iw_request_info *info,
                                        union iwreq_data *data, char *extra)
{
	int ret=0;
	//printk("====>%s()\n", __FUNCTION__);
	struct r8192_priv *priv = ieee80211_priv(dev);
	down(&priv->wx_sem);
	ret = ieee80211_wx_set_auth(priv->ieee80211, info, &(data->param), extra);
	up(&priv->wx_sem);
	return ret;
}