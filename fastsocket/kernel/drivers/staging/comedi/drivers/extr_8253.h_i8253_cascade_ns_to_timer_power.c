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
 int TRIG_ROUND_MASK ; 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 

__attribute__((used)) static inline void i8253_cascade_ns_to_timer_power(int i8253_osc_base,
						   unsigned int *d1,
						   unsigned int *d2,
						   unsigned int *nanosec,
						   int round_mode)
{
	int div1, div2;
	int base;

	for (div1 = 2; div1 <= (1 << 16); div1 <<= 1) {
		base = i8253_osc_base * div1;
		round_mode &= TRIG_ROUND_MASK;
		switch (round_mode) {
		case TRIG_ROUND_NEAREST:
		default:
			div2 = (*nanosec + base / 2) / base;
			break;
		case TRIG_ROUND_DOWN:
			div2 = (*nanosec) / base;
			break;
		case TRIG_ROUND_UP:
			div2 = (*nanosec + base - 1) / base;
			break;
		}
		if (div2 < 2)
			div2 = 2;
		if (div2 <= 65536) {
			*nanosec = div2 * base;
			*d1 = div1 & 0xffff;
			*d2 = div2 & 0xffff;
			return;
		}
	}

	/* shouldn't get here */
	div1 = 0x10000;
	div2 = 0x10000;
	*nanosec = div1 * div2 * i8253_osc_base;
	*d1 = div1 & 0xffff;
	*d2 = div2 & 0xffff;
}