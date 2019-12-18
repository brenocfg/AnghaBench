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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ack (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_cts (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 

int hostap_80211_get_hdrlen(__le16 fc)
{
	if (ieee80211_is_data(fc) && ieee80211_has_a4 (fc))
		return 30; /* Addr4 */
	else if (ieee80211_is_cts(fc) || ieee80211_is_ack(fc))
		return 10;
	else if (ieee80211_is_ctl(fc))
		return 16;

	return 24;
}