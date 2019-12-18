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
#define  TRIG_ROUND_DOWN 130 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 

__attribute__((used)) static int dt282x_ns_to_timer(int *nanosec, int round_mode)
{
	int prescale, base, divider;

	for (prescale = 0; prescale < 16; prescale++) {
		if (prescale == 1)
			continue;
		base = 250 * (1 << prescale);
		switch (round_mode) {
		case TRIG_ROUND_NEAREST:
		default:
			divider = (*nanosec + base / 2) / base;
			break;
		case TRIG_ROUND_DOWN:
			divider = (*nanosec) / base;
			break;
		case TRIG_ROUND_UP:
			divider = (*nanosec + base - 1) / base;
			break;
		}
		if (divider < 256) {
			*nanosec = divider * base;
			return (prescale << 8) | (255 - divider);
		}
	}
	base = 250 * (1 << 15);
	divider = 255;
	*nanosec = divider * base;
	return (15 << 8) | (255 - divider);
}