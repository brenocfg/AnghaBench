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
union iwreq_data {int /*<<< orphan*/  name; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {int modulation; int mode; scalar_t__ state; } ;

/* Variables and functions */
 int IEEE80211_CCK_MODULATION ; 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IEEE80211_LINKED_SCANNING ; 
 scalar_t__ IEEE80211_NOLINK ; 
 int IEEE80211_OFDM_MODULATION ; 
 int IEEE_N_24G ; 
 int IEEE_N_5G ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int ieee80211_wx_get_name(struct ieee80211_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	strlcpy(wrqu->name, "802.11", IFNAMSIZ);
	if(ieee->modulation & IEEE80211_CCK_MODULATION){
		strlcat(wrqu->name, "b", IFNAMSIZ);
		if(ieee->modulation & IEEE80211_OFDM_MODULATION)
			strlcat(wrqu->name, "/g", IFNAMSIZ);
	}else if(ieee->modulation & IEEE80211_OFDM_MODULATION)
		strlcat(wrqu->name, "g", IFNAMSIZ);
	if (ieee->mode & (IEEE_N_24G | IEEE_N_5G))
		strlcat(wrqu->name, "/n", IFNAMSIZ);

	if((ieee->state == IEEE80211_LINKED) ||
		(ieee->state == IEEE80211_LINKED_SCANNING))
		strlcat(wrqu->name, "  link", IFNAMSIZ);
	else if(ieee->state != IEEE80211_NOLINK)
		strlcat(wrqu->name, " .....", IFNAMSIZ);


	return 0;
}