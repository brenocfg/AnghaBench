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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct chan_freq_power {scalar_t__ channel; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct chan_freq_power*) ; 
 struct chan_freq_power* channel_freq_power_UN_BG ; 

u32 lbs_chan_2_freq(u8 chan)
{
	struct chan_freq_power *cf;
	u16 i;
	u32 freq = 0;

	cf = channel_freq_power_UN_BG;

	for (i = 0; i < ARRAY_SIZE(channel_freq_power_UN_BG); i++) {
		if (chan == cf[i].channel)
			freq = cf[i].freq;
	}

	return freq;
}