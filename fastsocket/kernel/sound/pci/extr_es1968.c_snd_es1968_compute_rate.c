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
typedef  int u32 ;
struct es1968 {int clock; } ;

/* Variables and functions */

__attribute__((used)) static u32 snd_es1968_compute_rate(struct es1968 *chip, u32 freq)
{
	u32 rate = (freq << 16) / chip->clock;
#if 0 /* XXX: do we need this? */ 
	if (rate > 0x10000)
		rate = 0x10000;
#endif
	return rate;
}