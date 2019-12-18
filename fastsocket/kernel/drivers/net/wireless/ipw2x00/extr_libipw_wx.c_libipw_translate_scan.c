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
struct TYPE_12__ {int mask; int rssi; scalar_t__ signal; scalar_t__ noise; } ;
struct libipw_network {char* ssid; size_t mode; int capability; int rates_len; int rates_ex_len; int* rates_ex; int* rates; int wpa_ie_len; int rsn_ie_len; int /*<<< orphan*/  channel; int /*<<< orphan*/  last_scanned; int /*<<< orphan*/  rsn_ie; int /*<<< orphan*/  wpa_ie; TYPE_5__ stats; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  bssid; } ;
struct libipw_device {scalar_t__ perfect_rssi; scalar_t__ worst_rssi; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_13__ {int flags; int length; } ;
struct TYPE_11__ {int updated; int qual; scalar_t__ level; scalar_t__ noise; } ;
struct TYPE_10__ {int value; scalar_t__ disabled; scalar_t__ fixed; } ;
struct TYPE_9__ {int e; int /*<<< orphan*/  i; int /*<<< orphan*/  m; } ;
struct TYPE_8__ {char* sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_14__ {TYPE_6__ data; TYPE_4__ qual; TYPE_3__ bitrate; TYPE_2__ freq; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; TYPE_1__ ap_addr; } ;
struct iw_event {int cmd; TYPE_7__ u; } ;
typedef  int /*<<< orphan*/  iwe ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 void* IWEVCUSTOM ; 
 void* IWEVGENIE ; 
 int IWEVQUAL ; 
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
 int IW_QUAL_LEVEL_UPDATED ; 
 int IW_QUAL_NOISE_INVALID ; 
 int IW_QUAL_NOISE_UPDATED ; 
 int IW_QUAL_QUAL_INVALID ; 
 int IW_QUAL_QUAL_UPDATED ; 
 int LIBIPW_CH_INVALID ; 
 int LIBIPW_CH_RADAR_DETECT ; 
 int LIBIPW_STATMASK_NOISE ; 
 int LIBIPW_STATMASK_RSSI ; 
 int LIBIPW_STATMASK_SIGNAL ; 
 int MAX_CUSTOM_LEN ; 
 int MAX_WPA_IE_LEN ; 
 int SIOCGIWAP ; 
 int SIOCGIWENCODE ; 
 int SIOCGIWESSID ; 
 int SIOCGIWFREQ ; 
 int SIOCGIWMODE ; 
 int SIOCGIWNAME ; 
 int SIOCGIWRATE ; 
 int WLAN_CAPABILITY_ESS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int elapsed_jiffies_msecs (int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_event (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_point (struct iw_request_info*,char*,char*,struct iw_event*,char*) ; 
 char* iwe_stream_add_value (struct iw_request_info*,char*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 int iwe_stream_lcp_len (struct iw_request_info*) ; 
 int /*<<< orphan*/  libipw_channel_to_freq (struct libipw_device*,int /*<<< orphan*/ ) ; 
 int libipw_get_channel_flags (struct libipw_device*,int /*<<< orphan*/ ) ; 
 char** libipw_modes ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iw_event*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static char *libipw_translate_scan(struct libipw_device *ieee,
				      char *start, char *stop,
				      struct libipw_network *network,
				      struct iw_request_info *info)
{
	char custom[MAX_CUSTOM_LEN];
	char *p;
	struct iw_event iwe;
	int i, j;
	char *current_val;	/* For rates */
	u8 rate;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(iwe.u.ap_addr.sa_data, network->bssid, ETH_ALEN);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_ADDR_LEN);

	/* Remaining entries will be displayed in the order we provide them */

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	iwe.u.data.length = min(network->ssid_len, (u8) 32);
	start = iwe_stream_add_point(info, start, stop,
				     &iwe, network->ssid);

	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	snprintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11%s",
		 libipw_modes[network->mode]);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_CHAR_LEN);

	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	if (network->capability & (WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS)) {
		if (network->capability & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		else
			iwe.u.mode = IW_MODE_ADHOC;

		start = iwe_stream_add_event(info, start, stop,
					     &iwe, IW_EV_UINT_LEN);
	}

	/* Add channel and frequency */
	/* Note : userspace automatically computes channel using iwrange */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = libipw_channel_to_freq(ieee, network->channel);
	iwe.u.freq.e = 6;
	iwe.u.freq.i = 0;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_FREQ_LEN);

	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	if (network->capability & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	else
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	start = iwe_stream_add_point(info, start, stop,
				     &iwe, network->ssid);

	/* Add basic and extended rates */
	/* Rate : stuffing multiple values in a single event require a bit
	 * more of magic - Jean II */
	current_val = start + iwe_stream_lcp_len(info);
	iwe.cmd = SIOCGIWRATE;
	/* Those two flags are ignored... */
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;

	for (i = 0, j = 0; i < network->rates_len;) {
		if (j < network->rates_ex_len &&
		    ((network->rates_ex[j] & 0x7F) <
		     (network->rates[i] & 0x7F)))
			rate = network->rates_ex[j++] & 0x7F;
		else
			rate = network->rates[i++] & 0x7F;
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((rate & 0x7f) * 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, start, current_val,
						   stop, &iwe, IW_EV_PARAM_LEN);
	}
	for (; j < network->rates_ex_len; j++) {
		rate = network->rates_ex[j] & 0x7F;
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((rate & 0x7f) * 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, start, current_val,
						   stop, &iwe, IW_EV_PARAM_LEN);
	}
	/* Check if we added any rate */
	if ((current_val - start) > iwe_stream_lcp_len(info))
		start = current_val;

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED |
	    IW_QUAL_NOISE_UPDATED;

	if (!(network->stats.mask & LIBIPW_STATMASK_RSSI)) {
		iwe.u.qual.updated |= IW_QUAL_QUAL_INVALID |
		    IW_QUAL_LEVEL_INVALID;
		iwe.u.qual.qual = 0;
	} else {
		if (ieee->perfect_rssi == ieee->worst_rssi)
			iwe.u.qual.qual = 100;
		else
			iwe.u.qual.qual =
			    (100 *
			     (ieee->perfect_rssi - ieee->worst_rssi) *
			     (ieee->perfect_rssi - ieee->worst_rssi) -
			     (ieee->perfect_rssi - network->stats.rssi) *
			     (15 * (ieee->perfect_rssi - ieee->worst_rssi) +
			      62 * (ieee->perfect_rssi -
				    network->stats.rssi))) /
			    ((ieee->perfect_rssi -
			      ieee->worst_rssi) * (ieee->perfect_rssi -
						   ieee->worst_rssi));
		if (iwe.u.qual.qual > 100)
			iwe.u.qual.qual = 100;
		else if (iwe.u.qual.qual < 1)
			iwe.u.qual.qual = 0;
	}

	if (!(network->stats.mask & LIBIPW_STATMASK_NOISE)) {
		iwe.u.qual.updated |= IW_QUAL_NOISE_INVALID;
		iwe.u.qual.noise = 0;
	} else {
		iwe.u.qual.noise = network->stats.noise;
	}

	if (!(network->stats.mask & LIBIPW_STATMASK_SIGNAL)) {
		iwe.u.qual.updated |= IW_QUAL_LEVEL_INVALID;
		iwe.u.qual.level = 0;
	} else {
		iwe.u.qual.level = network->stats.signal;
	}

	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_QUAL_LEN);

	iwe.cmd = IWEVCUSTOM;
	p = custom;

	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
		start = iwe_stream_add_point(info, start, stop, &iwe, custom);

	memset(&iwe, 0, sizeof(iwe));
	if (network->wpa_ie_len) {
		char buf[MAX_WPA_IE_LEN];
		memcpy(buf, network->wpa_ie, network->wpa_ie_len);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = network->wpa_ie_len;
		start = iwe_stream_add_point(info, start, stop, &iwe, buf);
	}

	memset(&iwe, 0, sizeof(iwe));
	if (network->rsn_ie_len) {
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
		      " Last beacon: %ums ago",
		      elapsed_jiffies_msecs(network->last_scanned));
	iwe.u.data.length = p - custom;
	if (iwe.u.data.length)
		start = iwe_stream_add_point(info, start, stop, &iwe, custom);

	/* Add spectrum management information */
	iwe.cmd = -1;
	p = custom;
	p += snprintf(p, MAX_CUSTOM_LEN - (p - custom), " Channel flags: ");

	if (libipw_get_channel_flags(ieee, network->channel) &
	    LIBIPW_CH_INVALID) {
		iwe.cmd = IWEVCUSTOM;
		p += snprintf(p, MAX_CUSTOM_LEN - (p - custom), "INVALID ");
	}

	if (libipw_get_channel_flags(ieee, network->channel) &
	    LIBIPW_CH_RADAR_DETECT) {
		iwe.cmd = IWEVCUSTOM;
		p += snprintf(p, MAX_CUSTOM_LEN - (p - custom), "DFS ");
	}

	if (iwe.cmd == IWEVCUSTOM) {
		iwe.u.data.length = p - custom;
		start = iwe_stream_add_point(info, start, stop, &iwe, custom);
	}

	return start;
}