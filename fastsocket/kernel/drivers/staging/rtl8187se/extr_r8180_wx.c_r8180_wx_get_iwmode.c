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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct r8180_priv {int /*<<< orphan*/  wx_sem; struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {int modulation; } ;

/* Variables and functions */
 int IEEE80211_CCK_MODULATION ; 
 int IEEE80211_OFDM_MODULATION ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8180_wx_get_iwmode(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee;
	int ret = 0;



	down(&priv->wx_sem);

	ieee = priv->ieee80211;

	strcpy(extra, "802.11");
	if(ieee->modulation & IEEE80211_CCK_MODULATION) {
		strcat(extra, "b");
		if(ieee->modulation & IEEE80211_OFDM_MODULATION)
			strcat(extra, "/g");
	} else if(ieee->modulation & IEEE80211_OFDM_MODULATION)
		strcat(extra, "g");

	up(&priv->wx_sem);

	return ret;
}