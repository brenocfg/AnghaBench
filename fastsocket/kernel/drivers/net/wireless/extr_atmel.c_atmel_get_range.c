#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_8__ {int qual; int level; void* updated; scalar_t__ noise; } ;
struct TYPE_7__ {int qual; int level; void* updated; scalar_t__ noise; } ;
struct iw_range {int min_nwid; int max_nwid; int num_channels; int num_frequency; int* bitrate; int num_bitrates; int max_rts; int min_frag; int max_frag; int* encoding_size; int num_encoding_sizes; int max_encoding_tokens; int min_retry; int max_retry; scalar_t__ r_time_flags; void* retry_flags; void* retry_capa; void* we_version_compiled; void* we_version_source; scalar_t__ pm_capa; void* pmt_flags; void* pmp_flags; scalar_t__ min_rts; scalar_t__ sensitivity; TYPE_3__ avg_qual; TYPE_2__ max_qual; TYPE_1__* freq; } ;
struct iw_point {int length; } ;
struct atmel_private {scalar_t__ reg_domain; } ;
struct TYPE_9__ {scalar_t__ reg_domain; int max; int min; } ;
struct TYPE_6__ {int i; int m; int e; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 void* IW_POWER_ON ; 
 void* IW_QUAL_NOISE_INVALID ; 
 void* IW_RETRY_LIMIT ; 
 void* WIRELESS_EXT ; 
 TYPE_4__* channel_table ; 
 int ieee80211_dsss_chan_to_freq (int) ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_range(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_point *dwrq,
			   char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	struct iw_range *range = (struct iw_range *) extra;
	int k, i, j;

	dwrq->length = sizeof(struct iw_range);
	memset(range, 0, sizeof(struct iw_range));
	range->min_nwid = 0x0000;
	range->max_nwid = 0x0000;
	range->num_channels = 0;
	for (j = 0; j < ARRAY_SIZE(channel_table); j++)
		if (priv->reg_domain == channel_table[j].reg_domain) {
			range->num_channels = channel_table[j].max - channel_table[j].min + 1;
			break;
		}
	if (range->num_channels != 0) {
		for (k = 0, i = channel_table[j].min; i <= channel_table[j].max; i++) {
			range->freq[k].i = i; /* List index */

			/* Values in MHz -> * 10^5 * 10 */
			range->freq[k].m = (ieee80211_dsss_chan_to_freq(i) *
					    100000);
			range->freq[k++].e = 1;
		}
		range->num_frequency = k;
	}

	range->max_qual.qual = 100;
	range->max_qual.level = 100;
	range->max_qual.noise = 0;
	range->max_qual.updated = IW_QUAL_NOISE_INVALID;

	range->avg_qual.qual = 50;
	range->avg_qual.level = 50;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = IW_QUAL_NOISE_INVALID;

	range->sensitivity = 0;

	range->bitrate[0] =  1000000;
	range->bitrate[1] =  2000000;
	range->bitrate[2] =  5500000;
	range->bitrate[3] = 11000000;
	range->num_bitrates = 4;

	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = 4;

	range->pmp_flags = IW_POWER_ON;
	range->pmt_flags = IW_POWER_ON;
	range->pm_capa = 0;

	range->we_version_source = WIRELESS_EXT;
	range->we_version_compiled = WIRELESS_EXT;
	range->retry_capa = IW_RETRY_LIMIT ;
	range->retry_flags = IW_RETRY_LIMIT;
	range->r_time_flags = 0;
	range->min_retry = 1;
	range->max_retry = 65535;

	return 0;
}