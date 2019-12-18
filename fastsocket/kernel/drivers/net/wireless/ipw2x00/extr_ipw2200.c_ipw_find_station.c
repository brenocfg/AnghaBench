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
struct ipw_priv {int num_stations; int /*<<< orphan*/ * stations; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IPW_INVALID_STATION ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ipw_find_station(struct ipw_priv *priv, u8 * bssid)
{
	int i;

	for (i = 0; i < priv->num_stations; i++)
		if (!memcmp(priv->stations[i], bssid, ETH_ALEN))
			return i;

	return IPW_INVALID_STATION;
}