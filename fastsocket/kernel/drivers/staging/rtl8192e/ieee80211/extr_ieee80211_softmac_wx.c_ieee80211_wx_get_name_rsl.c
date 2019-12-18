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
struct ieee80211_device {int modulation; int mode; } ;

/* Variables and functions */
 int IEEE80211_CCK_MODULATION ; 
 int IEEE80211_OFDM_MODULATION ; 
 int IEEE_N_24G ; 
 int IEEE_N_5G ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int ieee80211_wx_get_name(struct ieee80211_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	strcpy(wrqu->name, "802.11");
	if(ieee->modulation & IEEE80211_CCK_MODULATION)
		strcat(wrqu->name, "b");
	if(ieee->modulation & IEEE80211_OFDM_MODULATION)
		strcat(wrqu->name, "g");
	if (ieee->mode & (IEEE_N_24G | IEEE_N_5G))
		strcat(wrqu->name, "n");
	return 0;
}