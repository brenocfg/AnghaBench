#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct iw_request_info {int dummy; } ;
struct TYPE_13__ {int flags; int length; } ;
struct TYPE_11__ {scalar_t__ level; int updated; int /*<<< orphan*/  noise; int /*<<< orphan*/  qual; } ;
struct TYPE_9__ {int value; scalar_t__ disabled; scalar_t__ fixed; } ;
struct TYPE_8__ {int /*<<< orphan*/  i; scalar_t__ e; int /*<<< orphan*/  m; } ;
struct TYPE_12__ {char* sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_14__ {TYPE_6__ data; TYPE_4__ qual; TYPE_2__ bitrate; TYPE_1__ freq; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; TYPE_5__ ap_addr; } ;
struct iw_event {TYPE_7__ u; void* cmd; } ;
struct TYPE_10__ {scalar_t__ signal; scalar_t__ rssi; int mask; int /*<<< orphan*/  noise; int /*<<< orphan*/  signalstrength; } ;
struct ieee80211_network {scalar_t__ ssid_len; char* ssid; size_t mode; int capability; int rates_len; int rates_ex_len; int* rates_ex; int* rates; int wpa_ie_len; int rsn_ie_len; int last_scanned; int /*<<< orphan*/  rsn_ie; int /*<<< orphan*/  wpa_ie; TYPE_3__ stats; int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; } ;
struct ieee80211_device {int dummy; } ;
typedef  int /*<<< orphan*/  iwe ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ETH_ALEN ; 
 int HZ ; 
 int IEEE80211_STATMASK_NOISE ; 
 int IEEE80211_STATMASK_RSSI ; 
 int IEEE80211_STATMASK_SIGNAL ; 
 int IEEE80211_STATMASK_WEMASK ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 void* IWEVCUSTOM ; 
 void* IWEVGENIE ; 
 void* IWEVQUAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_NOKEY ; 
 int /*<<< orphan*/  IW_EV_ADDR_LEN ; 
 int /*<<< orphan*/  IW_EV_CHAR_LEN ; 
 int /*<<< orphan*/  IW_EV_FREQ_LEN ; 
 int /*<<< orphan*/  IW_EV_PARAM_LEN ; 
 int /*<<< orphan*/  IW_EV_QUAL_LEN ; 
 int /*<<< orphan*/  IW_EV_UINT_LEN ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
 int IW_QUAL_LEVEL_INVALID ; 
 int IW_QUAL_NOISE_INVALID ; 
 int IW_QUAL_QUAL_INVALID ; 
 int MAX_CUSTOM_LEN ; 
 int MAX_WPA_IE_LEN ; 
 void* SIOCGIWAP ; 
 void* SIOCGIWENCODE ; 
 void* SIOCGIWESSID ; 
 void* SIOCGIWFREQ ; 
 void* SIOCGIWMODE ; 
 void* SIOCGIWNAME ; 
 void* SIOCGIWRATE ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 char** ieee80211_modes ; 
 char* iwe_stream_add_event (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_point (struct iw_request_info*,char*,char*,struct iw_event*,char*) ; 
 int jiffies ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iw_event*,int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static inline char *rtl818x_translate_scan(struct ieee80211_device *ieee,
		                           char *start, char *stop,
                                           struct ieee80211_network *network,
                                           struct iw_request_info *info)
{
	char custom[MAX_CUSTOM_LEN];
	char *p;
	struct iw_event iwe;
	int i, j;
	u8 max_rate, rate;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(iwe.u.ap_addr.sa_data, network->bssid, ETH_ALEN);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_ADDR_LEN);

	/* Remaining entries will be displayed in the order we provide them */

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	//YJ,modified,080903,for hidden ap
	//if (network->flags & NETWORK_EMPTY_ESSID) {
	if (network->ssid_len == 0) {
	//YJ,modified,080903,end
		iwe.u.data.length = sizeof("<hidden>");
		start = iwe_stream_add_point(info, start, stop, &iwe, "<hidden>");
	} else {
		iwe.u.data.length = min(network->ssid_len, (u8)32);
		start = iwe_stream_add_point(info, start, stop, &iwe, network->ssid);
	}
	//printk("ESSID: %s\n",network->ssid);
	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	snprintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11%s", ieee80211_modes[network->mode]);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_CHAR_LEN);

        /* Add mode */
        iwe.cmd = SIOCGIWMODE;
        if (network->capability &
	    (WLAN_CAPABILITY_BSS | WLAN_CAPABILITY_IBSS)) {
		if (network->capability & WLAN_CAPABILITY_BSS)
			iwe.u.mode = IW_MODE_MASTER;
		else
			iwe.u.mode = IW_MODE_ADHOC;

		start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_UINT_LEN);
	}

        /* Add frequency/channel */
	iwe.cmd = SIOCGIWFREQ;
/*	iwe.u.freq.m = ieee80211_frequency(network->channel, network->mode);
	iwe.u.freq.e = 3; */
	iwe.u.freq.m = network->channel;
	iwe.u.freq.e = 0;
	iwe.u.freq.i = 0;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_FREQ_LEN);

	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	if (network->capability & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	else
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	start = iwe_stream_add_point(info, start, stop, &iwe, network->ssid);

	/* Add basic and extended rates */
	max_rate = 0;
	p = custom;
	p += snprintf(p, MAX_CUSTOM_LEN - (p - custom), " Rates (Mb/s): ");
	for (i = 0, j = 0; i < network->rates_len; ) {
		if (j < network->rates_ex_len &&
		    ((network->rates_ex[j] & 0x7F) <
		     (network->rates[i] & 0x7F)))
			rate = network->rates_ex[j++] & 0x7F;
		else
			rate = network->rates[i++] & 0x7F;
		if (rate > max_rate)
			max_rate = rate;
		p += snprintf(p, MAX_CUSTOM_LEN - (p - custom),
			      "%d%s ", rate >> 1, (rate & 1) ? ".5" : "");
	}
	for (; j < network->rates_ex_len; j++) {
		rate = network->rates_ex[j] & 0x7F;
		p += snprintf(p, MAX_CUSTOM_LEN - (p - custom),
			      "%d%s ", rate >> 1, (rate & 1) ? ".5" : "");
		if (rate > max_rate)
			max_rate = rate;
	}

	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;
	iwe.u.bitrate.value = max_rate * 500000;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_PARAM_LEN);

	iwe.cmd = IWEVCUSTOM;
	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
		start = iwe_stream_add_point(info, start, stop, &iwe, custom);

	/* Add quality statistics */
	/* TODO: Fix these values... */
	if (network->stats.signal == 0 || network->stats.rssi == 0)
	printk("========>signal:%d, rssi:%d\n", network->stats.signal, network->stats.rssi);
	iwe.cmd = IWEVQUAL;
//	printk("SIGNAL: %d,RSSI: %d,NOISE: %d\n",network->stats.signal,network->stats.rssi,network->stats.noise);
	iwe.u.qual.qual = network->stats.signalstrength;
	iwe.u.qual.level = network->stats.signal;
	iwe.u.qual.noise = network->stats.noise;
	iwe.u.qual.updated = network->stats.mask & IEEE80211_STATMASK_WEMASK;
	if (!(network->stats.mask & IEEE80211_STATMASK_RSSI))
		iwe.u.qual.updated |= IW_QUAL_LEVEL_INVALID;
	if (!(network->stats.mask & IEEE80211_STATMASK_NOISE))
		iwe.u.qual.updated |= IW_QUAL_NOISE_INVALID;
	if (!(network->stats.mask & IEEE80211_STATMASK_SIGNAL))
		iwe.u.qual.updated |= IW_QUAL_QUAL_INVALID;
	iwe.u.qual.updated = 7;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_QUAL_LEN);

	iwe.cmd = IWEVCUSTOM;
	p = custom;

	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
		start = iwe_stream_add_point(info, start, stop, &iwe, custom);

		memset(&iwe, 0, sizeof(iwe));
        if (network->wpa_ie_len) {
	//	printk("wpa_ie_len:%d\n", network->wpa_ie_len);
                char buf[MAX_WPA_IE_LEN];
                memcpy(buf, network->wpa_ie, network->wpa_ie_len);
                iwe.cmd = IWEVGENIE;
                iwe.u.data.length = network->wpa_ie_len;
                start = iwe_stream_add_point(info, start, stop, &iwe, buf);
        }

        memset(&iwe, 0, sizeof(iwe));
        if (network->rsn_ie_len) {
	//	printk("=====>rsn_ie_len:\n", network->rsn_ie_len);
                char buf[MAX_WPA_IE_LEN];
                memcpy(buf, network->rsn_ie, network->rsn_ie_len);
                iwe.cmd = IWEVGENIE;
                iwe.u.data.length = network->rsn_ie_len;
		start = iwe_stream_add_point(info, start, stop, &iwe, buf);
	}

	/* Add EXTRA: Age to display seconds since last beacon/probe response
	 * for given network. */
	iwe.cmd = IWEVCUSTOM;
	p = custom;
	p += snprintf(p, MAX_CUSTOM_LEN - (p - custom),
		      " Last beacon: %lums ago", (jiffies - network->last_scanned) / (HZ / 100));
	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
		start = iwe_stream_add_point(info, start, stop, &iwe, custom);

	return start;
}