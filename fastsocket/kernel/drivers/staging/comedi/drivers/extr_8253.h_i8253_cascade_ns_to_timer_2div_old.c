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

__attribute__((used)) static inline void i8253_cascade_ns_to_timer_2div_old(int i8253_osc_base,
						      unsigned int *d1,
						      unsigned int *d2,
						      unsigned int *nanosec,
						      int round_mode)
{
	int divider;
	int div1, div2;
	int div1_glb, div2_glb, ns_glb;
	int div1_lub, div2_lub, ns_lub;
	int ns;

	divider = (*nanosec + i8253_osc_base / 2) / i8253_osc_base;

	/* find 2 integers 1<={x,y}<=65536 such that x*y is
	   close to divider */

	div1_lub = div2_lub = 0;
	div1_glb = div2_glb = 0;

	ns_glb = 0;
	ns_lub = 0xffffffff;

	div2 = 0x10000;
	for (div1 = divider / 65536 + 1; div1 < div2; div1++) {
		div2 = divider / div1;

		ns = i8253_osc_base * div1 * div2;
		if (ns <= *nanosec && ns > ns_glb) {
			ns_glb = ns;
			div1_glb = div1;
			div2_glb = div2;
		}

		div2++;
		if (div2 <= 65536) {
			ns = i8253_osc_base * div1 * div2;
			if (ns > *nanosec && ns < ns_lub) {
				ns_lub = ns;
				div1_lub = div1;
				div2_lub = div2;
			}
		}
	}

	*nanosec = div1_lub * div2_lub * i8253_osc_base;
	*d1 = div1_lub & 0xffff;
	*d2 = div2_lub & 0xffff;
	return;
}