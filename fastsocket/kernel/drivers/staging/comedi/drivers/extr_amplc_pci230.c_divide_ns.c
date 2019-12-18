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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
#define  TRIG_ROUND_DOWN 130 
 unsigned int TRIG_ROUND_MASK ; 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 
 scalar_t__ UINT_MAX ; 
 unsigned int do_div (scalar_t__,unsigned int) ; 

__attribute__((used)) static unsigned int divide_ns(uint64_t ns, unsigned int timebase,
			      unsigned int round_mode)
{
	uint64_t div;
	unsigned int rem;

	div = ns;
	rem = do_div(div, timebase);
	round_mode &= TRIG_ROUND_MASK;
	switch (round_mode) {
	default:
	case TRIG_ROUND_NEAREST:
		div += (rem + (timebase / 2)) / timebase;
		break;
	case TRIG_ROUND_DOWN:
		break;
	case TRIG_ROUND_UP:
		div += (rem + timebase - 1) / timebase;
		break;
	}
	return div > UINT_MAX ? UINT_MAX : (unsigned int)div;
}