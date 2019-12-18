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

/* Variables and functions */

long TranslateToDbm8185(u8 SignalStrengthIndex)
{
	long SignalPower;

	// Translate to dBm (x=0.5y-95).
	SignalPower = (long)((SignalStrengthIndex + 1) >> 1);
	SignalPower -= 95;

	return SignalPower;
}