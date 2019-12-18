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
 scalar_t__* ratio2dB ; 

int
il3945_calc_db_from_ratio(int sig_ratio)
{
	/* 1000:1 or higher just report as 60 dB */
	if (sig_ratio >= 1000)
		return 60;

	/* 100:1 or higher, divide by 10 and use table,
	 *   add 20 dB to make up for divide by 10 */
	if (sig_ratio >= 100)
		return 20 + (int)ratio2dB[sig_ratio / 10];

	/* We shouldn't see this */
	if (sig_ratio < 1)
		return 0;

	/* Use table for ratios 1:1 - 99:1 */
	return (int)ratio2dB[sig_ratio];
}