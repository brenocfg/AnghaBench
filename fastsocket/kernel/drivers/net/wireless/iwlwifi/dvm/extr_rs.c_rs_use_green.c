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
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool rs_use_green(struct ieee80211_sta *sta)
{
	/*
	 * There's a bug somewhere in this code that causes the
	 * scaling to get stuck because GF+SGI can't be combined
	 * in SISO rates. Until we find that bug, disable GF, it
	 * has only limited benefit and we still interoperate with
	 * GF APs since we can always receive GF transmissions.
	 */
	return false;
}