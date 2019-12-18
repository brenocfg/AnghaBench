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
struct TYPE_3__ {scalar_t__ disabled; int value; int /*<<< orphan*/  flags; } ;
union iwreq_data {TYPE_1__ power; } ;
struct r8180_priv {int /*<<< orphan*/  wx_sem; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ bHwRadioOff; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_POWER_ALL_R ; 
 int /*<<< orphan*/  IW_POWER_TIMEOUT ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int ieee80211_wx_set_power (TYPE_2__*,struct iw_request_info*,union iwreq_data*,char*) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8180_wx_set_power(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	int ret;
	struct r8180_priv *priv = ieee80211_priv(dev);


	if(priv->ieee80211->bHwRadioOff)
		return 0;

	down(&priv->wx_sem);
	printk("=>>>>>>>>>>=============================>set power:%d,%d!\n",wrqu->power.disabled, wrqu->power.flags);
	if (wrqu->power.disabled==0) {
		wrqu->power.flags|=IW_POWER_ALL_R;
		wrqu->power.flags|=IW_POWER_TIMEOUT;
		wrqu->power.value =1000;
	}

	ret = ieee80211_wx_set_power(priv->ieee80211, info, wrqu, extra);

	up(&priv->wx_sem);

	return ret;
}