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
struct TYPE_4__ {scalar_t__ value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_2__ rts; } ;
struct r8180_priv {scalar_t__ rts; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ bHwRadioOff; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RTS_THRESHOLD ; 
 int EINVAL ; 
 scalar_t__ MAX_RTS_THRESHOLD ; 
 scalar_t__ MIN_RTS_THRESHOLD ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static int r8180_wx_set_rts(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	struct r8180_priv *priv = ieee80211_priv(dev);


	if(priv->ieee80211->bHwRadioOff)
		return 0;

	if (wrqu->rts.disabled)
		priv->rts = DEFAULT_RTS_THRESHOLD;
	else {
		if (wrqu->rts.value < MIN_RTS_THRESHOLD ||
		    wrqu->rts.value > MAX_RTS_THRESHOLD)
			return -EINVAL;

		priv->rts = wrqu->rts.value;
	}

	return 0;
}