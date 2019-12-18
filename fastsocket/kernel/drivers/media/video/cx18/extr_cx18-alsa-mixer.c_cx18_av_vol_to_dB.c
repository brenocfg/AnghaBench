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

__attribute__((used)) static inline int cx18_av_vol_to_dB(int v)
{
	if (v < (23 << 9))
		v = (23 << 9);
	else if (v > (127 << 9))
		v = (127 << 9);
	return (v >> 9) - 119;
}