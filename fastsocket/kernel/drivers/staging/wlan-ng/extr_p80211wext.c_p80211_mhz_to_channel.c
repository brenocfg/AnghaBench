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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u8 p80211_mhz_to_channel(u16 mhz)
{
	if (mhz >= 5000)
		return (mhz - 5000) / 5;

	if (mhz == 2482)
		return 14;

	if (mhz >= 2407)
		return (mhz - 2407) / 5;

	return 0;
}