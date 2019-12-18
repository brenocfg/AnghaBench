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

__attribute__((used)) static int
calc_gus_envelope_time(int rate, int start, int end)
{
	int r, p, t;
	r = (3 - ((rate >> 6) & 3)) * 3;
	p = rate & 0x3f;
	t = end - start;
	if (t < 0) t = -t;
	if (13 > r)
		t = t << (13 - r);
	else
		t = t >> (r - 13);
	return (t * 10) / (p * 441);
}