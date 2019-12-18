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
 unsigned int TIMER_BASE ; 
#define  TRIG_ROUND_DOWN 130 
 unsigned int TRIG_ROUND_MASK ; 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 

__attribute__((used)) static unsigned int get_divisor(unsigned int ns, unsigned int flags)
{
	unsigned int divisor;

	switch (flags & TRIG_ROUND_MASK) {
	case TRIG_ROUND_UP:
		divisor = (ns + TIMER_BASE - 1) / TIMER_BASE;
		break;
	case TRIG_ROUND_DOWN:
		divisor = ns / TIMER_BASE;
		break;
	case TRIG_ROUND_NEAREST:
	default:
		divisor = (ns + TIMER_BASE / 2) / TIMER_BASE;
		break;
	}
	return divisor;
}