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

__attribute__((used)) static int tmrHw_divide(int num, int denom)
{
	int r;
	int t = 1;

	/* Shift denom and t up to the largest value to optimize algorithm */
	/* t contains the units of each divide */
	while ((denom & 0x40000000) == 0) {	/* fails if denom=0 */
		denom = denom << 1;
		t = t << 1;
	}

	/* Intialize the result */
	r = 0;

	do {
		/* Determine if there exists a positive remainder */
		if ((num - denom) >= 0) {
			/* Accumlate t to the result and calculate a new remainder */
			num = num - denom;
			r = r + t;
		}
		/* Continue to shift denom and shift t down to 0 */
		denom = denom >> 1;
		t = t >> 1;
	} while (t != 0);
	return r;
}