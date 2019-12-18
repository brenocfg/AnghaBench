#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_rx_stats {int dummy; } ;
struct TYPE_4__ {unsigned char signalstrength; int noise; unsigned char signal; scalar_t__ ac_aci_acm_aifsn; } ;
struct ieee80211_network {int rates_len; int rates_ex_len; int ssid_len; int wpa_ie_len; int rsn_ie_len; int QoS_Enable; int CountryIeLen; TYPE_1__* CountryIeBuf; int /*<<< orphan*/  Turbo_Enable; int /*<<< orphan*/  SignalStrength; TYPE_1__* wmm_param; int /*<<< orphan*/  wmm_info; int /*<<< orphan*/  last_scanned; TYPE_1__* rsn_ie; TYPE_1__* wpa_ie; int /*<<< orphan*/ * last_dtim_sta_time; int /*<<< orphan*/  dtim_data; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  atim_window; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/ * time_stamp; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  channel; TYPE_1__* ssid; int /*<<< orphan*/  HighestOperaRate; TYPE_1__* rates_ex; TYPE_1__* rates; int /*<<< orphan*/  capability; TYPE_1__ stats; } ;

/* Variables and functions */
 int WME_AC_PRAM_LEN ; 
 unsigned char ieee80211_TranslateToDbm (unsigned char) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

inline void update_network(struct ieee80211_network *dst,
				  struct ieee80211_network *src)
{
	unsigned char quality = src->stats.signalstrength;
	unsigned char signal = 0;
	unsigned char noise = 0;
        if(dst->stats.signalstrength > 0) {
                quality = (dst->stats.signalstrength * 5 + src->stats.signalstrength + 5)/6;
        }
	signal = ieee80211_TranslateToDbm(quality);
	//noise = signal - src->stats.noise;
	if(dst->stats.noise > 0)
		noise = (dst->stats.noise * 5 + src->stats.noise)/6;
        //if(strcmp(dst->ssid, "linksys_lzm000") == 0)
//	printk("ssid:%s, quality:%d, signal:%d\n", dst->ssid, quality, signal);
	memcpy(&dst->stats, &src->stats, sizeof(struct ieee80211_rx_stats));
	dst->stats.signalstrength = quality;
	dst->stats.signal = signal;
//	printk("==================>stats.signal is %d\n",dst->stats.signal);
	dst->stats.noise = noise;


	dst->capability = src->capability;
	memcpy(dst->rates, src->rates, src->rates_len);
	dst->rates_len = src->rates_len;
	memcpy(dst->rates_ex, src->rates_ex, src->rates_ex_len);
	dst->rates_ex_len = src->rates_ex_len;
	dst->HighestOperaRate= src->HighestOperaRate;
	//printk("==========>in %s: src->ssid is %s,chan is %d\n",__func__,src->ssid,src->channel);

	//YJ,add,080819,for hidden ap
	if(src->ssid_len > 0)
	{
		//if(src->ssid_len == 13)
		//	printk("=====================>>>>>>>> Dst ssid: %s Src ssid: %s\n", dst->ssid, src->ssid);
		memset(dst->ssid, 0, dst->ssid_len);
		dst->ssid_len = src->ssid_len;
		memcpy(dst->ssid, src->ssid, src->ssid_len);
	}
	//YJ,add,080819,for hidden ap,end

	dst->channel = src->channel;
	dst->mode = src->mode;
	dst->flags = src->flags;
	dst->time_stamp[0] = src->time_stamp[0];
	dst->time_stamp[1] = src->time_stamp[1];

	dst->beacon_interval = src->beacon_interval;
	dst->listen_interval = src->listen_interval;
	dst->atim_window = src->atim_window;
	dst->dtim_period = src->dtim_period;
	dst->dtim_data = src->dtim_data;
	dst->last_dtim_sta_time[0] = src->last_dtim_sta_time[0];
	dst->last_dtim_sta_time[1] = src->last_dtim_sta_time[1];
//	printk("update:%s, dtim_period:%x, dtim_data:%x\n", src->ssid, src->dtim_period, src->dtim_data);
	memcpy(dst->wpa_ie, src->wpa_ie, src->wpa_ie_len);
	dst->wpa_ie_len = src->wpa_ie_len;
	memcpy(dst->rsn_ie, src->rsn_ie, src->rsn_ie_len);
	dst->rsn_ie_len = src->rsn_ie_len;

	dst->last_scanned = jiffies;
	/* dst->last_associate is not overwritten */
// disable QoS process now, added by David 2006/7/25
#if 1
	dst->wmm_info = src->wmm_info; //sure to exist in beacon or probe response frame.
/*
	if((dst->wmm_info^src->wmm_info)&0x0f) {//Param Set Count change, update Parameter
	  memcpy(dst->wmm_param, src->wmm_param, IEEE80211_AC_PRAM_LEN);
	}
*/
	if(src->wmm_param[0].ac_aci_acm_aifsn|| \
	   src->wmm_param[1].ac_aci_acm_aifsn|| \
	   src->wmm_param[2].ac_aci_acm_aifsn|| \
	   src->wmm_param[3].ac_aci_acm_aifsn) {
	  memcpy(dst->wmm_param, src->wmm_param, WME_AC_PRAM_LEN);
	}
	dst->QoS_Enable = src->QoS_Enable;
#else
	dst->QoS_Enable = 1;//for Rtl8187 simulation
#endif
	dst->SignalStrength = src->SignalStrength;
	dst->Turbo_Enable = src->Turbo_Enable;
	dst->CountryIeLen = src->CountryIeLen;
	memcpy(dst->CountryIeBuf, src->CountryIeBuf, src->CountryIeLen);
}