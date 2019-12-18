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
 int* sa2400_rf_rssi_map ; 

__attribute__((used)) static u8 sa2400_rf_calc_rssi(u8 agc, u8 sq)
{
	if (sq == 0x80)
		return 1;

	if (sq > 78)
		return 32;

	/* TODO: recalc sa2400_rf_rssi_map to avoid mult / div */
	return 65 * sa2400_rf_rssi_map[sq] / 100;
}