#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct iw_request_info {int dummy; } ;
struct TYPE_13__ {size_t length; int flags; } ;
struct TYPE_11__ {int value; } ;
struct TYPE_10__ {int level; int noise; int updated; } ;
struct TYPE_9__ {int m; int e; } ;
struct TYPE_12__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_14__ {TYPE_5__ data; TYPE_3__ bitrate; TYPE_2__ qual; TYPE_1__ freq; int /*<<< orphan*/  mode; TYPE_4__ ap_addr; } ;
struct iw_event {TYPE_6__ u; void* cmd; } ;
struct hostap_bss_info {int* ssid; size_t ssid_len; int* bssid; int capab_info; int chan; int wpa_ie_len; char* wpa_ie; int rsn_ie_len; char* rsn_ie; } ;
struct hfa384x_hostscan_result {int* ssid; int* bssid; int* sup_rates; int /*<<< orphan*/  atim; int /*<<< orphan*/  rate; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  anl; int /*<<< orphan*/  sl; int /*<<< orphan*/  chid; int /*<<< orphan*/  capability; int /*<<< orphan*/  ssid_len; } ;
struct TYPE_15__ {scalar_t__ last_scan_type; } ;
typedef  TYPE_7__ local_info_t ;
typedef  int /*<<< orphan*/  iwe ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* HFA384X_LEVEL_TO_dBm (int) ; 
 void* IWEVCUSTOM ; 
 void* IWEVGENIE ; 
 void* IWEVQUAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_NOKEY ; 
 int /*<<< orphan*/  IW_EV_ADDR_LEN ; 
 int /*<<< orphan*/  IW_EV_FREQ_LEN ; 
 int /*<<< orphan*/  IW_EV_PARAM_LEN ; 
 int /*<<< orphan*/  IW_EV_QUAL_LEN ; 
 int /*<<< orphan*/  IW_EV_UINT_LEN ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
 int IW_QUAL_DBM ; 
 int IW_QUAL_LEVEL_UPDATED ; 
 int IW_QUAL_NOISE_UPDATED ; 
 int IW_QUAL_QUAL_INVALID ; 
 int MAX_WPA_IE_LEN ; 
 scalar_t__ PRISM2_HOSTSCAN ; 
 void* SIOCGIWAP ; 
 void* SIOCGIWENCODE ; 
 void* SIOCGIWESSID ; 
 void* SIOCGIWFREQ ; 
 void* SIOCGIWMODE ; 
 void* SIOCGIWRATE ; 
 int WLAN_CAPABILITY_ESS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int* freq_list ; 
 char* iwe_stream_add_event (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_point (struct iw_request_info*,char*,char*,struct iw_event*,...) ; 
 char* iwe_stream_add_value (struct iw_request_info*,char*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 int iwe_stream_lcp_len (struct iw_request_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iw_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 void* strlen (char*) ; 

__attribute__((used)) static char * __prism2_translate_scan(local_info_t *local,
				      struct iw_request_info *info,
				      struct hfa384x_hostscan_result *scan,
				      struct hostap_bss_info *bss,
				      char *current_ev, char *end_buf)
{
	int i, chan;
	struct iw_event iwe;
	char *current_val;
	u16 capabilities;
	u8 *pos;
	u8 *ssid, *bssid;
	size_t ssid_len;
	char *buf;

	if (bss) {
		ssid = bss->ssid;
		ssid_len = bss->ssid_len;
		bssid = bss->bssid;
	} else {
		ssid = scan->ssid;
		ssid_len = le16_to_cpu(scan->ssid_len);
		bssid = scan->bssid;
	}
	if (ssid_len > 32)
		ssid_len = 32;

	/* First entry *MUST* be the AP MAC address */
	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(iwe.u.ap_addr.sa_data, bssid, ETH_ALEN);
	current_ev = iwe_stream_add_event(info, current_ev, end_buf, &iwe,
					  IW_EV_ADDR_LEN);

	/* Other entries will be displayed in the order we give them */

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.length = ssid_len;
	iwe.u.data.flags = 1;
	current_ev = iwe_stream_add_point(info, current_ev, end_buf,
					  &iwe, ssid);

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWMODE;
	if (bss) {
		capabilities = bss->capab_info;
	} else {
		capabilities = le16_to_cpu(scan->capability);
	}
	if (capabilities & (WLAN_CAPABILITY_ESS |
			    WLAN_CAPABILITY_IBSS)) {
		if (capabilities & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		else
			iwe.u.mode = IW_MODE_ADHOC;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_UINT_LEN);
	}

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWFREQ;
	if (scan) {
		chan = le16_to_cpu(scan->chid);
	} else if (bss) {
		chan = bss->chan;
	} else {
		chan = 0;
	}

	if (chan > 0) {
		iwe.u.freq.m = freq_list[chan - 1] * 100000;
		iwe.u.freq.e = 1;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_FREQ_LEN);
	}

	if (scan) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVQUAL;
		if (local->last_scan_type == PRISM2_HOSTSCAN) {
			iwe.u.qual.level = le16_to_cpu(scan->sl);
			iwe.u.qual.noise = le16_to_cpu(scan->anl);
		} else {
			iwe.u.qual.level =
				HFA384X_LEVEL_TO_dBm(le16_to_cpu(scan->sl));
			iwe.u.qual.noise =
				HFA384X_LEVEL_TO_dBm(le16_to_cpu(scan->anl));
		}
		iwe.u.qual.updated = IW_QUAL_LEVEL_UPDATED
			| IW_QUAL_NOISE_UPDATED
			| IW_QUAL_QUAL_INVALID
			| IW_QUAL_DBM;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_QUAL_LEN);
	}

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWENCODE;
	if (capabilities & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	else
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	current_ev = iwe_stream_add_point(info, current_ev, end_buf, &iwe, "");

	/* TODO: add SuppRates into BSS table */
	if (scan) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = SIOCGIWRATE;
		current_val = current_ev + iwe_stream_lcp_len(info);
		pos = scan->sup_rates;
		for (i = 0; i < sizeof(scan->sup_rates); i++) {
			if (pos[i] == 0)
				break;
			/* Bit rate given in 500 kb/s units (+ 0x80) */
			iwe.u.bitrate.value = ((pos[i] & 0x7f) * 500000);
			current_val = iwe_stream_add_value(
				info, current_ev, current_val, end_buf, &iwe,
				IW_EV_PARAM_LEN);
		}
		/* Check if we added any event */
		if ((current_val - current_ev) > iwe_stream_lcp_len(info))
			current_ev = current_val;
	}

	/* TODO: add BeaconInt,resp_rate,atim into BSS table */
	buf = kmalloc(MAX_WPA_IE_LEN * 2 + 30, GFP_ATOMIC);
	if (buf && scan) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVCUSTOM;
		sprintf(buf, "bcn_int=%d", le16_to_cpu(scan->beacon_interval));
		iwe.u.data.length = strlen(buf);
		current_ev = iwe_stream_add_point(info, current_ev, end_buf,
						  &iwe, buf);

		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVCUSTOM;
		sprintf(buf, "resp_rate=%d", le16_to_cpu(scan->rate));
		iwe.u.data.length = strlen(buf);
		current_ev = iwe_stream_add_point(info, current_ev, end_buf,
						  &iwe, buf);

		if (local->last_scan_type == PRISM2_HOSTSCAN &&
		    (capabilities & WLAN_CAPABILITY_IBSS)) {
			memset(&iwe, 0, sizeof(iwe));
			iwe.cmd = IWEVCUSTOM;
			sprintf(buf, "atim=%d", le16_to_cpu(scan->atim));
			iwe.u.data.length = strlen(buf);
			current_ev = iwe_stream_add_point(info, current_ev,
							  end_buf, &iwe, buf);
		}
	}
	kfree(buf);

	if (bss && bss->wpa_ie_len > 0 && bss->wpa_ie_len <= MAX_WPA_IE_LEN) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = bss->wpa_ie_len;
		current_ev = iwe_stream_add_point(info, current_ev, end_buf,
						  &iwe, bss->wpa_ie);
	}

	if (bss && bss->rsn_ie_len > 0 && bss->rsn_ie_len <= MAX_WPA_IE_LEN) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = bss->rsn_ie_len;
		current_ev = iwe_stream_add_point(info, current_ev, end_buf,
						  &iwe, bss->rsn_ie);
	}

	return current_ev;
}