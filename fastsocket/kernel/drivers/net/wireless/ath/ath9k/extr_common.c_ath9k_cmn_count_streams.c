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

int ath9k_cmn_count_streams(unsigned int chainmask, int max)
{
	int streams = 0;

	do {
		if (++streams == max)
			break;
	} while ((chainmask = chainmask & (chainmask - 1)));

	return streams;
}