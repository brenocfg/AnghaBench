#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct TYPE_5__ {size_t sta_id; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  rate_n_flags; scalar_t__ station_flags; TYPE_2__ sta; scalar_t__ mode; } ;
struct il_station_entry {int used; TYPE_3__ sta; } ;
struct TYPE_4__ {size_t bcast_id; int max_stations; } ;
struct il_priv {scalar_t__ band; int /*<<< orphan*/  num_stations; struct il_station_entry* stations; TYPE_1__ hw_params; } ;
struct il_addsta_cmd {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSOC (char*,size_t,size_t const*) ; 
 int /*<<< orphan*/  D_INFO (char*,size_t) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 size_t IL_AP_ID ; 
 size_t IL_INVALID_STATION ; 
 int IL_STA_DRIVER_ACTIVE ; 
 int IL_STA_ID ; 
 int IL_STA_UCODE_ACTIVE ; 
 int IL_STA_UCODE_INPROGRESS ; 
 int RATE_1M_PLCP ; 
 int RATE_6M_PLCP ; 
 int RATE_MCS_ANT_AB_MSK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,size_t const*) ; 
 int /*<<< orphan*/  il_set_ht_add_station (struct il_priv*,size_t,struct ieee80211_sta*) ; 
 scalar_t__ is_broadcast_ether_addr (size_t const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

u8
il_prep_station(struct il_priv *il, const u8 *addr, bool is_ap,
		struct ieee80211_sta *sta)
{
	struct il_station_entry *station;
	int i;
	u8 sta_id = IL_INVALID_STATION;
	u16 rate;

	if (is_ap)
		sta_id = IL_AP_ID;
	else if (is_broadcast_ether_addr(addr))
		sta_id = il->hw_params.bcast_id;
	else
		for (i = IL_STA_ID; i < il->hw_params.max_stations; i++) {
			if (ether_addr_equal(il->stations[i].sta.sta.addr,
					     addr)) {
				sta_id = i;
				break;
			}

			if (!il->stations[i].used &&
			    sta_id == IL_INVALID_STATION)
				sta_id = i;
		}

	/*
	 * These two conditions have the same outcome, but keep them
	 * separate
	 */
	if (unlikely(sta_id == IL_INVALID_STATION))
		return sta_id;

	/*
	 * uCode is not able to deal with multiple requests to add a
	 * station. Keep track if one is in progress so that we do not send
	 * another.
	 */
	if (il->stations[sta_id].used & IL_STA_UCODE_INPROGRESS) {
		D_INFO("STA %d already in process of being added.\n", sta_id);
		return sta_id;
	}

	if ((il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE) &&
	    (il->stations[sta_id].used & IL_STA_UCODE_ACTIVE) &&
	    ether_addr_equal(il->stations[sta_id].sta.sta.addr, addr)) {
		D_ASSOC("STA %d (%pM) already added, not adding again.\n",
			sta_id, addr);
		return sta_id;
	}

	station = &il->stations[sta_id];
	station->used = IL_STA_DRIVER_ACTIVE;
	D_ASSOC("Add STA to driver ID %d: %pM\n", sta_id, addr);
	il->num_stations++;

	/* Set up the C_ADD_STA command to send to device */
	memset(&station->sta, 0, sizeof(struct il_addsta_cmd));
	memcpy(station->sta.sta.addr, addr, ETH_ALEN);
	station->sta.mode = 0;
	station->sta.sta.sta_id = sta_id;
	station->sta.station_flags = 0;

	/*
	 * OK to call unconditionally, since local stations (IBSS BSSID
	 * STA and broadcast STA) pass in a NULL sta, and mac80211
	 * doesn't allow HT IBSS.
	 */
	il_set_ht_add_station(il, sta_id, sta);

	/* 3945 only */
	rate = (il->band == IEEE80211_BAND_5GHZ) ? RATE_6M_PLCP : RATE_1M_PLCP;
	/* Turn on both antennas for the station... */
	station->sta.rate_n_flags = cpu_to_le16(rate | RATE_MCS_ANT_AB_MSK);

	return sta_id;

}