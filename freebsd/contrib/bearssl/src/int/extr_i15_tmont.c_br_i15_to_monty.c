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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_i15_muladd_small (int*,int /*<<< orphan*/ ,int const*) ; 

void
br_i15_to_monty(uint16_t *x, const uint16_t *m)
{
	unsigned k;

	for (k = (m[0] + 15) >> 4; k > 0; k --) {
		br_i15_muladd_small(x, 0, m);
	}
}