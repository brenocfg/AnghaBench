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
typedef  int u16_t ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {int qual; int level; int noise; } ;
struct iw_range {int we_version_source; int max_retry; int num_channels; int num_frequency; int sensitivity; int max_rts; int min_frag; int max_frag; int max_encoding_tokens; int num_encoding_sizes; int* encoding_size; int throughput; scalar_t__ num_bitrates; scalar_t__ min_rts; TYPE_2__ max_qual; TYPE_1__* freq; scalar_t__ min_retry; void* retry_flags; void* retry_capa; int /*<<< orphan*/  we_version_compiled; int /*<<< orphan*/  txpower_capa; } ;
struct iw_point {int dummy; } ;
struct TYPE_3__ {int i; int m; int e; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_MAX_FREQUENCIES ; 
 void* IW_RETRY_LIMIT ; 
 int /*<<< orphan*/  IW_TXPOW_DBM ; 
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int* channel_frequency_11A ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int num_band_a ; 
 int usbdrv_freq2chan (int) ; 
 int zfiWlanQueryAllowChannels (struct net_device*,int*) ; 

int usbdrvwext_giwrange(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_point *data, char *extra)
{
	struct iw_range *range = (struct iw_range *) extra;
	int i, val;
	/* int num_band_a; */
	u16_t channels[60];
	u16_t channel_num;

	if (!netif_running(dev))
		return -EINVAL;

	range->txpower_capa = IW_TXPOW_DBM;
	/* XXX what about min/max_pmp, min/max_pmt, etc. */

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 13;

	range->retry_capa = IW_RETRY_LIMIT;
	range->retry_flags = IW_RETRY_LIMIT;
	range->min_retry = 0;
	range->max_retry = 255;

	channel_num = zfiWlanQueryAllowChannels(dev, channels);

	/* Gurantee reported channel numbers is less
	* or equal to IW_MAX_FREQUENCIES
	*/
	if (channel_num > IW_MAX_FREQUENCIES)
		channel_num = IW_MAX_FREQUENCIES;

	val = 0;

	for (i = 0; i < channel_num; i++) {
		range->freq[val].i = usbdrv_freq2chan(channels[i]);
		range->freq[val].m = channels[i];
		range->freq[val].e = 6;
		val++;
	}

	range->num_channels = channel_num;
	range->num_frequency = channel_num;

	#if 0
	range->num_channels = 14; /* Only 2.4G */

	/* XXX need to filter against the regulatory domain &| active set */
	val = 0;
	/* B,G Bands */
	for (i = 1; i <= 14; i++) {
		range->freq[val].i = i;
		if (i == 14)
			range->freq[val].m = 2484000;
		else
			range->freq[val].m = (2412+(i-1)*5)*1000;
		range->freq[val].e = 3;
		val++;
	}

	num_band_a = (IW_MAX_FREQUENCIES - val);
	/* A Bands */
	for (i = 0; i < num_band_a; i++) {
		range->freq[val].i = channel_frequency_11A[2 * i];
		range->freq[val].m = channel_frequency_11A[2 * i + 1] * 1000;
		range->freq[val].e = 3;
		val++;
	}
	/* MIMO Rate Not Defined Now
	* For 802.11a, there are too more frequency.
	* We can't return them all.
	*/
	range->num_frequency = val;
	#endif

	/* Max of /proc/net/wireless */
	range->max_qual.qual = 100;  /* ??  92; */
	range->max_qual.level = 154; /* ?? */
	range->max_qual.noise = 154; /* ?? */
	range->sensitivity = 3;      /* ?? */

	/* XXX these need to be nsd-specific! */
	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;
	range->max_encoding_tokens = 4 /* NUM_WEPKEYS ?? */;
	range->num_encoding_sizes = 2; /* ?? */

	range->encoding_size[0] = 5; /* ?? WEP Key Encoding Size */
	range->encoding_size[1] = 13; /* ?? */

	/* XXX what about num_bitrates/throughput? */
	range->num_bitrates = 0; /* ?? */

	/* estimated max throughput
	* XXX need to cap it if we're running at ~2Mbps..
	*/

	range->throughput = 300000000;

	return 0;
}