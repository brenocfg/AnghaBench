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
typedef  int u8 ;
struct ipw_station_entry {int /*<<< orphan*/  mac_addr; scalar_t__ support_mode; scalar_t__ reserved; } ;
struct ipw_priv {int num_stations; int config; int /*<<< orphan*/ * stations; scalar_t__ missed_adhoc_beacons; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int CFG_ADHOC_PERSIST ; 
 int CFG_STATIC_CHANNEL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*,int*) ; 
 int IPW_INVALID_STATION ; 
 scalar_t__ IPW_STATION_TABLE_LOWER ; 
 int MAX_STATIONS ; 
 int /*<<< orphan*/  ipw_write_direct (struct ipw_priv*,scalar_t__,struct ipw_station_entry*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ipw_add_station(struct ipw_priv *priv, u8 * bssid)
{
	struct ipw_station_entry entry;
	int i;

	for (i = 0; i < priv->num_stations; i++) {
		if (!memcmp(priv->stations[i], bssid, ETH_ALEN)) {
			/* Another node is active in network */
			priv->missed_adhoc_beacons = 0;
			if (!(priv->config & CFG_STATIC_CHANNEL))
				/* when other nodes drop out, we drop out */
				priv->config &= ~CFG_ADHOC_PERSIST;

			return i;
		}
	}

	if (i == MAX_STATIONS)
		return IPW_INVALID_STATION;

	IPW_DEBUG_SCAN("Adding AdHoc station: %pM\n", bssid);

	entry.reserved = 0;
	entry.support_mode = 0;
	memcpy(entry.mac_addr, bssid, ETH_ALEN);
	memcpy(priv->stations[i], bssid, ETH_ALEN);
	ipw_write_direct(priv, IPW_STATION_TABLE_LOWER + i * sizeof(entry),
			 &entry, sizeof(entry));
	priv->num_stations++;

	return i;
}