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
struct minstrel_rate {void* ack_time; void* perfect_tx_time; } ;
struct ieee80211_rate {int flags; int /*<<< orphan*/  bitrate; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int IEEE80211_RATE_ERP_G ; 
 void* ieee80211_frame_duration (int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
calc_rate_durations(enum ieee80211_band band,
		    struct minstrel_rate *d,
		    struct ieee80211_rate *rate)
{
	int erp = !!(rate->flags & IEEE80211_RATE_ERP_G);

	d->perfect_tx_time = ieee80211_frame_duration(band, 1200,
			rate->bitrate, erp, 1);
	d->ack_time = ieee80211_frame_duration(band, 10,
			rate->bitrate, erp, 1);
}