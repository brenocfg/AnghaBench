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
u8 b43legacy_freq_to_channel_bg(int freq)
{
	u8 channel;

	if (freq == 2484)
		channel = 14;
	else
		channel = (freq - 2407) / 5;

	return channel;
}