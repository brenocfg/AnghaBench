#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct iw_request_info {int dummy; } ;
struct TYPE_19__ {int flags; int length; } ;
struct TYPE_18__ {int updated; int /*<<< orphan*/  noise; int /*<<< orphan*/  level; int /*<<< orphan*/  qual; } ;
struct TYPE_16__ {int value; scalar_t__ disabled; scalar_t__ fixed; } ;
struct TYPE_14__ {int /*<<< orphan*/  i; scalar_t__ e; int /*<<< orphan*/  m; } ;
struct TYPE_13__ {char* sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_20__ {TYPE_7__ data; TYPE_6__ qual; TYPE_4__ bitrate; TYPE_2__ freq; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; TYPE_1__ ap_addr; } ;
struct iw_event {TYPE_8__ u; void* cmd; } ;
struct TYPE_17__ {int mask; int /*<<< orphan*/  noise; int /*<<< orphan*/  rssi; int /*<<< orphan*/  signal; } ;
struct TYPE_15__ {int /*<<< orphan*/ * bdHTCapBuf; } ;
struct ieee80211_network {scalar_t__ ssid_len; char* ssid; int mode; int capability; int rates_len; int rates_ex_len; int* rates_ex; int* rates; int wpa_ie_len; int rsn_ie_len; int last_scanned; int /*<<< orphan*/  rsn_ie; int /*<<< orphan*/  wpa_ie; TYPE_5__ stats; TYPE_3__ bssht; int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; } ;
struct ieee80211_device {int dummy; } ;
typedef  int /*<<< orphan*/  iwe ;
struct TYPE_21__ {int /*<<< orphan*/  MCS; scalar_t__ ShortGI20Mhz; scalar_t__ ShortGI40Mhz; scalar_t__ ChlWidth; } ;
struct TYPE_12__ {char* mode_string; int /*<<< orphan*/  mode_size; } ;
typedef  TYPE_9__* PHT_CAPABILITY_ELE ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ARRAY_SIZE (TYPE_10__*) ; 
 int ETH_ALEN ; 
 int HTGetHighestMCSRate (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 int IEEE80211_STATMASK_NOISE ; 
 int IEEE80211_STATMASK_RSSI ; 
 int IEEE80211_STATMASK_SIGNAL ; 
 int IEEE80211_STATMASK_WEMASK ; 
 int IEEE_N_24G ; 
 int IFNAMSIZ ; 
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
 int*** MCS_DATA_RATE ; 
 int /*<<< orphan*/  MCS_FILTER_ALL ; 
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
 TYPE_10__* ieee80211_modes ; 
 char* iwe_stream_add_event_rsl (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_point (struct iw_request_info*,char*,char*,struct iw_event*,char*) ; 
 int jiffies ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iw_event*,int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *rtl819x_translate_scan(struct ieee80211_device *ieee,
 					   char *start, char *stop,
					   struct ieee80211_network *network,
                                           struct iw_request_info *info)
{
	char custom[MAX_CUSTOM_LEN];
	char proto_name[IFNAMSIZ];
	char *pname = proto_name;
	char *p;
	struct iw_event iwe;
	int i, j;
	u16 max_rate, rate;
	static u8	EWC11NHTCap[] = {0x00, 0x90, 0x4c, 0x33};

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(iwe.u.ap_addr.sa_data, network->bssid, ETH_ALEN);
	start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_ADDR_LEN);

	/* Remaining entries will be displayed in the order we provide them */

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
//	if (network->flags & NETWORK_EMPTY_ESSID) {
	if (network->ssid_len == 0) {
		iwe.u.data.length = sizeof("<hidden>");
                start = iwe_stream_add_point(info, start, stop, &iwe, "<hidden>");
        } else {
		iwe.u.data.length = min(network->ssid_len, (u8)32);
                start = iwe_stream_add_point(info, start, stop, &iwe, network->ssid);
        }
	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	for(i=0; i<ARRAY_SIZE(ieee80211_modes); i++) {
		if(network->mode&(1<<i)) {
			sprintf(pname,ieee80211_modes[i].mode_string,ieee80211_modes[i].mode_size);
			pname +=ieee80211_modes[i].mode_size;
		}
	}
	*pname = '\0';
	snprintf(iwe.u.name, IFNAMSIZ, "IEEE802.11%s", proto_name);
        start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_CHAR_LEN);
        /* Add mode */
        iwe.cmd = SIOCGIWMODE;
        if (network->capability &
	    (WLAN_CAPABILITY_BSS | WLAN_CAPABILITY_IBSS)) {
		if (network->capability & WLAN_CAPABILITY_BSS)
			iwe.u.mode = IW_MODE_MASTER;
		else
			iwe.u.mode = IW_MODE_ADHOC;
                start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_UINT_LEN);
        }

        /* Add frequency/channel */
	iwe.cmd = SIOCGIWFREQ;
/*	iwe.u.freq.m = ieee80211_frequency(network->channel, network->mode);
	iwe.u.freq.e = 3; */
	iwe.u.freq.m = network->channel;
	iwe.u.freq.e = 0;
	iwe.u.freq.i = 0;
        start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_FREQ_LEN);
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

	if (network->mode >= IEEE_N_24G)//add N rate here;
	{
		PHT_CAPABILITY_ELE ht_cap = NULL;
		bool is40M = false, isShortGI = false;
		u8 max_mcs = 0;
		if (!memcmp(network->bssht.bdHTCapBuf, EWC11NHTCap, 4))
			ht_cap = (PHT_CAPABILITY_ELE)&network->bssht.bdHTCapBuf[4];
		else
			ht_cap = (PHT_CAPABILITY_ELE)&network->bssht.bdHTCapBuf[0];
		is40M = (ht_cap->ChlWidth)?1:0;
		isShortGI = (ht_cap->ChlWidth)?
						((ht_cap->ShortGI40Mhz)?1:0):
						((ht_cap->ShortGI20Mhz)?1:0);

		max_mcs = HTGetHighestMCSRate(ieee, ht_cap->MCS, MCS_FILTER_ALL);
		rate = MCS_DATA_RATE[is40M][isShortGI][max_mcs&0x7f];
		if (rate > max_rate)
			max_rate = rate;
	}

	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;
	iwe.u.bitrate.value = max_rate * 500000;
        start = iwe_stream_add_event_rsl(info, start, stop, &iwe,
				     IW_EV_PARAM_LEN);

	iwe.cmd = IWEVCUSTOM;
	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
        start = iwe_stream_add_point(info, start, stop, &iwe, custom);

	/* Add quality statistics */
	/* TODO: Fix these values... */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.qual = network->stats.signal;
	iwe.u.qual.level = network->stats.rssi;
	iwe.u.qual.noise = network->stats.noise;
	iwe.u.qual.updated = network->stats.mask & IEEE80211_STATMASK_WEMASK;
	if (!(network->stats.mask & IEEE80211_STATMASK_RSSI))
		iwe.u.qual.updated |= IW_QUAL_LEVEL_INVALID;
	if (!(network->stats.mask & IEEE80211_STATMASK_NOISE))
		iwe.u.qual.updated |= IW_QUAL_NOISE_INVALID;
	if (!(network->stats.mask & IEEE80211_STATMASK_SIGNAL))
		iwe.u.qual.updated |= IW_QUAL_QUAL_INVALID;
	iwe.u.qual.updated = 7;
        start = iwe_stream_add_event_rsl(info, start, stop, &iwe, IW_EV_QUAL_LEN);
	iwe.cmd = IWEVCUSTOM;
	p = custom;

	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
            start = iwe_stream_add_point(info, start, stop, &iwe, custom);

	memset(&iwe, 0, sizeof(iwe));
	if (network->wpa_ie_len)
	{
		char buf[MAX_WPA_IE_LEN];
		memcpy(buf, network->wpa_ie, network->wpa_ie_len);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = network->wpa_ie_len;
                start = iwe_stream_add_point(info, start, stop, &iwe, buf);
        }
	memset(&iwe, 0, sizeof(iwe));
	if (network->rsn_ie_len)
	{
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