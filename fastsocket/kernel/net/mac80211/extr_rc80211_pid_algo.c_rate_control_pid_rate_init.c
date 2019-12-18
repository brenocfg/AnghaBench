#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rc_pid_sta_info {int /*<<< orphan*/  txrate_idx; } ;
struct rc_pid_rateinfo {int index; int rev_index; int diff; } ;
struct rc_pid_info {int norm_offset; struct rc_pid_rateinfo* rinfo; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_1__* bitrates; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_2__ {scalar_t__ bitrate; } ;

/* Variables and functions */
 scalar_t__ RC_PID_FAST_START ; 
 int /*<<< orphan*/  rate_lowest_index (struct ieee80211_supported_band*,struct ieee80211_sta*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
rate_control_pid_rate_init(void *priv, struct ieee80211_supported_band *sband,
			   struct ieee80211_sta *sta, void *priv_sta)
{
	struct rc_pid_sta_info *spinfo = priv_sta;
	struct rc_pid_info *pinfo = priv;
	struct rc_pid_rateinfo *rinfo = pinfo->rinfo;
	int i, j, tmp;
	bool s;

	/* TODO: This routine should consider using RSSI from previous packets
	 * as we need to have IEEE 802.1X auth succeed immediately after assoc..
	 * Until that method is implemented, we will use the lowest supported
	 * rate as a workaround. */

	/* Sort the rates. This is optimized for the most common case (i.e.
	 * almost-sorted CCK+OFDM rates). Kind of bubble-sort with reversed
	 * mapping too. */
	for (i = 0; i < sband->n_bitrates; i++) {
		rinfo[i].index = i;
		rinfo[i].rev_index = i;
		if (RC_PID_FAST_START)
			rinfo[i].diff = 0;
		else
			rinfo[i].diff = i * pinfo->norm_offset;
	}
	for (i = 1; i < sband->n_bitrates; i++) {
		s = false;
		for (j = 0; j < sband->n_bitrates - i; j++)
			if (unlikely(sband->bitrates[rinfo[j].index].bitrate >
				     sband->bitrates[rinfo[j + 1].index].bitrate)) {
				tmp = rinfo[j].index;
				rinfo[j].index = rinfo[j + 1].index;
				rinfo[j + 1].index = tmp;
				rinfo[rinfo[j].index].rev_index = j;
				rinfo[rinfo[j + 1].index].rev_index = j + 1;
				s = true;
			}
		if (!s)
			break;
	}

	spinfo->txrate_idx = rate_lowest_index(sband, sta);
}