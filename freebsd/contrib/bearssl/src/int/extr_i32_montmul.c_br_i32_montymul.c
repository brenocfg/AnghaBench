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
 int /*<<< orphan*/  MUL (int,int const) ; 
 int NEQ (int,int /*<<< orphan*/ ) ; 
 int NOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i32_sub (int*,int const*,int) ; 
 int /*<<< orphan*/  br_i32_zero (int*,int const) ; 

void
br_i32_montymul(uint32_t *d, const uint32_t *x, const uint32_t *y,
	const uint32_t *m, uint32_t m0i)
{
	size_t len, u, v;
	uint64_t dh;

	len = (m[0] + 31) >> 5;
	br_i32_zero(d, m[0]);
	dh = 0;
	for (u = 0; u < len; u ++) {
		uint32_t f, xu;
		uint64_t r1, r2, zh;

		xu = x[u + 1];
		f = (d[1] + x[u + 1] * y[1]) * m0i;
		r1 = 0;
		r2 = 0;
		for (v = 0; v < len; v ++) {
			uint64_t z;
			uint32_t t;

			z = (uint64_t)d[v + 1] + MUL(xu, y[v + 1]) + r1;
			r1 = z >> 32;
			t = (uint32_t)z;
			z = (uint64_t)t + MUL(f, m[v + 1]) + r2;
			r2 = z >> 32;
			if (v != 0) {
				d[v] = (uint32_t)z;
			}
		}
		zh = dh + r1 + r2;
		d[len] = (uint32_t)zh;
		dh = zh >> 32;
	}

	/*
	 * d[] may still be greater than m[] at that point; notably, the
	 * 'dh' word may be non-zero.
	 */
	br_i32_sub(d, m, NEQ(dh, 0) | NOT(br_i32_sub(d, m, 0)));
}