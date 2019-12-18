#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wpa_leader ;
typedef  int u16_t ;
struct zsBssInfo {char* ssid; int* capability; int channel; int* supportedRates; int* extSupportedRates; int* beaconInterval; scalar_t__* wpaIe; scalar_t__* rsnIe; int /*<<< orphan*/  signalQuality; int /*<<< orphan*/  signalStrength; int /*<<< orphan*/  bssid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_11__ {char length; int flags; } ;
struct TYPE_9__ {int value; scalar_t__ disabled; scalar_t__ fixed; } ;
struct TYPE_8__ {int updated; int /*<<< orphan*/  qual; scalar_t__ noise; int /*<<< orphan*/  level; } ;
struct TYPE_7__ {int m; int e; } ;
struct TYPE_10__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_12__ {TYPE_5__ data; TYPE_3__ bitrate; TYPE_2__ qual; TYPE_1__ freq; int /*<<< orphan*/  mode; TYPE_4__ ap_addr; } ;
struct iw_event {TYPE_6__ u; void* cmd; } ;
typedef  int /*<<< orphan*/  rsn_leader ;
typedef  int /*<<< orphan*/  iwe ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IEEE80211_ELEMID_RSN ; 
 void* IWEVCUSTOM ; 
 void* IWEVQUAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_NOKEY ; 
 int /*<<< orphan*/  IW_EV_ADDR_LEN ; 
 int /*<<< orphan*/  IW_EV_FREQ_LEN ; 
 long IW_EV_LCP_LEN ; 
 int /*<<< orphan*/  IW_EV_PARAM_LEN ; 
 int /*<<< orphan*/  IW_EV_QUAL_LEN ; 
 int /*<<< orphan*/  IW_EV_UINT_LEN ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
 int IW_QUAL_LEVEL_UPDATED ; 
 int IW_QUAL_NOISE_UPDATED ; 
 int IW_QUAL_QUAL_UPDATED ; 
 void* SIOCGIWAP ; 
 void* SIOCGIWENCODE ; 
 void* SIOCGIWESSID ; 
 void* SIOCGIWFREQ ; 
 void* SIOCGIWMODE ; 
 void* SIOCGIWRATE ; 
 void* encode_ie (char*,int,scalar_t__*,scalar_t__,char const*,int) ; 
 char* iwe_stream_add_event (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_point (struct iw_request_info*,char*,char*,struct iw_event*,char*) ; 
 char* iwe_stream_add_value (struct iw_request_info*,char*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iw_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char strlen (char*) ; 

char *usbdrv_translate_scan(struct net_device *dev,
	struct iw_request_info *info, char *current_ev,
	char *end_buf, struct zsBssInfo *list)
{
	struct iw_event iwe;   /* Temporary buffer */
	u16_t capabilities;
	char *current_val;     /* For rates */
	char *last_ev;
	int i;
	char    buf[64*2 + 30];

	last_ev = current_ev;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(iwe.u.ap_addr.sa_data, list->bssid, ETH_ALEN);
	current_ev = iwe_stream_add_event(info,	current_ev,
					end_buf, &iwe, IW_EV_ADDR_LEN);

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	/* Other entries will be displayed in the order we give them */

	/* Add the ESSID */
	iwe.u.data.length = list->ssid[1];
	if (iwe.u.data.length > 32)
		iwe.u.data.length = 32;
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	current_ev = iwe_stream_add_point(info,	current_ev,
					end_buf, &iwe, &list->ssid[2]);

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	capabilities = (list->capability[1] << 8) + list->capability[0];
	if (capabilities & (0x01 | 0x02)) {
		if (capabilities & 0x01)
			iwe.u.mode = IW_MODE_MASTER;
		else
			iwe.u.mode = IW_MODE_ADHOC;
			current_ev = iwe_stream_add_event(info,	current_ev,
						end_buf, &iwe, IW_EV_UINT_LEN);
	}

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	/* Add frequency */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = list->channel;
	/* Channel frequency in KHz */
	if (iwe.u.freq.m > 14) {
		if ((184 <= iwe.u.freq.m) && (iwe.u.freq.m <= 196))
			iwe.u.freq.m = 4000 + iwe.u.freq.m * 5;
		else
			iwe.u.freq.m = 5000 + iwe.u.freq.m * 5;
	} else {
		if (iwe.u.freq.m == 14)
			iwe.u.freq.m = 2484;
		else
			iwe.u.freq.m = 2412 + (iwe.u.freq.m - 1) * 5;
	}
	iwe.u.freq.e = 6;
	current_ev = iwe_stream_add_event(info, current_ev,
					end_buf, &iwe, IW_EV_FREQ_LEN);

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED
				| IW_QUAL_NOISE_UPDATED;
	iwe.u.qual.level = list->signalStrength;
	iwe.u.qual.noise = 0;
	iwe.u.qual.qual = list->signalQuality;
	current_ev = iwe_stream_add_event(info,	current_ev,
					end_buf, &iwe, IW_EV_QUAL_LEN);

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	/* Add encryption capability */

	iwe.cmd = SIOCGIWENCODE;
	if (capabilities & 0x10)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	else
		iwe.u.data.flags = IW_ENCODE_DISABLED;

	iwe.u.data.length = 0;
	current_ev = iwe_stream_add_point(info,	current_ev,
					end_buf, &iwe, list->ssid);

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	/* Rate : stuffing multiple values in a single event require a bit
	* more of magic
	*/
	current_val = current_ev + IW_EV_LCP_LEN;

	iwe.cmd = SIOCGIWRATE;
	/* Those two flags are ignored... */
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;

	for (i = 0 ; i < list->supportedRates[1] ; i++) {
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((list->supportedRates[i+2] & 0x7f)
					* 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, current_ev,
				current_val, end_buf, &iwe, IW_EV_PARAM_LEN);

		/* Ran out of buffer */
		if (last_ev == current_val)
			return end_buf;

		last_ev = current_val;
	}

	for (i = 0 ; i < list->extSupportedRates[1] ; i++) {
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((list->extSupportedRates[i+2] & 0x7f)
					* 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, current_ev,
				current_val, end_buf, &iwe, IW_EV_PARAM_LEN);

		/* Ran out of buffer */
		if (last_ev == current_val)
			return end_buf;

		last_ev = current_ev;
	}

	/* Check if we added any event */
	if ((current_val - current_ev) > IW_EV_LCP_LEN)
		current_ev = current_val;
		#define IEEE80211_ELEMID_RSN 0x30
	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = IWEVCUSTOM;
	snprintf(buf, sizeof(buf), "bcn_int=%d", (list->beaconInterval[1] << 8)
						+ list->beaconInterval[0]);
	iwe.u.data.length = strlen(buf);
	current_ev = iwe_stream_add_point(info, current_ev,
						end_buf, &iwe, buf);

	/* Ran out of buffer */
	if (last_ev == current_ev)
		return end_buf;

	last_ev = current_ev;

	if (list->wpaIe[1] != 0) {
		static const char rsn_leader[] = "rsn_ie=";
		static const char wpa_leader[] = "wpa_ie=";

		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVCUSTOM;
		if (list->wpaIe[0] == IEEE80211_ELEMID_RSN)
			iwe.u.data.length = encode_ie(buf, sizeof(buf),
					list->wpaIe, list->wpaIe[1]+2,
					rsn_leader, sizeof(rsn_leader)-1);
		else
			iwe.u.data.length = encode_ie(buf, sizeof(buf),
					list->wpaIe, list->wpaIe[1]+2,
					wpa_leader, sizeof(wpa_leader)-1);

		if (iwe.u.data.length != 0)
			current_ev = iwe_stream_add_point(info, current_ev,
							end_buf, &iwe, buf);

		/* Ran out of buffer */
		if (last_ev == current_ev)
			return end_buf;

		last_ev = current_ev;
	}

	if (list->rsnIe[1] != 0) {
		static const char rsn_leader[] = "rsn_ie=";
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVCUSTOM;

		if (list->rsnIe[0] == IEEE80211_ELEMID_RSN) {
			iwe.u.data.length = encode_ie(buf, sizeof(buf),
			list->rsnIe, list->rsnIe[1]+2,
			rsn_leader, sizeof(rsn_leader)-1);
			if (iwe.u.data.length != 0)
				current_ev = iwe_stream_add_point(info,
					current_ev, end_buf,  &iwe, buf);

			/* Ran out of buffer */
			if (last_ev == current_ev)
				return end_buf;

			last_ev = current_ev;
		}
	}
	/* The other data in the scan result are not really
	* interesting, so for now drop it
	*/
	return current_ev;
}