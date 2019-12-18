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

__attribute__((used)) static int dt3k_ns_to_timer(unsigned int timer_base, unsigned int *nanosec,
			    unsigned int round_mode)
{
	int divider, base, prescale;

	/* This function needs improvment */
	/* Don't know if divider==0 works. */

	for (prescale = 0; prescale < 16; prescale++) {
		base = timer_base * (prescale + 1);
		switch (round_mode) {
		case TRIG_ROUND_NEAREST:
		default:
			divider = (*nanosec + base / 2) / base;
			break;
		case TRIG_ROUND_DOWN:
			divider = (*nanosec) / base;
			break;
		case TRIG_ROUND_UP:
			divider = (*nanosec) / base;
			break;
		}
		if (divider < 65536) {
			*nanosec = divider * base;
			return (prescale << 16) | (divider);
		}
	}

	prescale = 15;
	base = timer_base * (1 << prescale);
	divider = 65535;
	*nanosec = divider * base;
	return (prescale << 16) | (divider);
}