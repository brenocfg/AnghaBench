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
struct r8180_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_2__ {int active_scan; scalar_t__ bHwRadioOff; } ;

/* Variables and functions */
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static int r8180_wx_set_scan_type(struct net_device *dev, struct iw_request_info *aa, union
 iwreq_data *wrqu, char *p){

 	struct r8180_priv *priv = ieee80211_priv(dev);
	int *parms=(int*)p;
	int mode=parms[0];

	if(priv->ieee80211->bHwRadioOff)
		return 0;

	priv->ieee80211->active_scan = mode;

	return 1;
}