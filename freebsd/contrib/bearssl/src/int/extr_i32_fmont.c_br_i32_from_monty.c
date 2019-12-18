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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int MUL (int,int const) ; 
 int /*<<< orphan*/  NOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i32_sub (int*,int const*,int /*<<< orphan*/ ) ; 

void
br_i32_from_monty(uint32_t *x, const uint32_t *m, uint32_t m0i)
{
	size_t len, u, v;

	len = (m[0] + 31) >> 5;
	for (u = 0; u < len; u ++) {
		uint32_t f;
		uint64_t cc;

		f = x[1] * m0i;
		cc = 0;
		for (v = 0; v < len; v ++) {
			uint64_t z;

			z = (uint64_t)x[v + 1] + MUL(f, m[v + 1]) + cc;
			cc = z >> 32;
			if (v != 0) {
				x[v] = (uint32_t)z;
			}
		}
		x[len] = (uint32_t)cc;
	}

	/*
	 * We may have to do an extra subtraction, but only if the
	 * value in x[] is indeed greater than or equal to that of m[],
	 * which is why we must do two calls (first call computes the
	 * carry, second call performs the subtraction only if the carry
	 * is 0).
	 */
	br_i32_sub(x, m, NOT(br_i32_sub(x, m, 0)));
}