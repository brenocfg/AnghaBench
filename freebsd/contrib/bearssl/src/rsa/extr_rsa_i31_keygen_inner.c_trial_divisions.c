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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMALL_PRIMES ; 
 int /*<<< orphan*/  br_i31_decode_reduce (int*,int /*<<< orphan*/ ,int,int const*) ; 
 int br_i31_moddiv (int*,int*,int const*,int,int*) ; 
 int br_i31_ninv31 (int const) ; 

__attribute__((used)) static uint32_t
trial_divisions(const uint32_t *x, uint32_t *t)
{
	uint32_t *y;
	uint32_t x0i;

	y = t;
	t += 1 + ((x[0] + 31) >> 5);
	x0i = br_i31_ninv31(x[1]);
	br_i31_decode_reduce(y, SMALL_PRIMES, sizeof SMALL_PRIMES, x);
	return br_i31_moddiv(y, y, x, x0i, t);
}