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

__attribute__((used)) static inline
int b43legacy_channel_to_freq_bg(u8 channel)
{
	int freq;

	if (channel == 14)
		freq = 2484;
	else
		freq = 2407 + (5 * channel);

	return freq;
}