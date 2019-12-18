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

/* Variables and functions */

int
ieee80211_TranslateToDbm(
	unsigned char SignalStrengthIndex	// 0-100 index.
	)
{
	unsigned char SignalPower; // in dBm.

	// Translate to dBm (x=0.5y-95).
	SignalPower = (int)SignalStrengthIndex * 7 / 10;
	SignalPower -= 95;

	return SignalPower;
}