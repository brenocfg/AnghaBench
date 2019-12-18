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

__attribute__((used)) static u16 p80211_channel_to_mhz(u8 ch, int dot11a)
{

	if (ch == 0)
		return 0;
	if (ch > 200)
		return 0;

	/* 5G */
	if (dot11a)
		return 5000 + (5 * ch);

	/* 2.4G */
	if (ch == 14)
		return 2484;

	if ((ch < 14) && (ch > 0))
		return 2407 + (5 * ch);

	return 0;
}