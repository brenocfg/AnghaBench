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
 unsigned int gf256red (unsigned int) ; 

__attribute__((used)) static void
inv_mix_columns(unsigned *state)
{
	int i;

	for (i = 0; i < 16; i += 4) {
		unsigned s0, s1, s2, s3;
		unsigned t0, t1, t2, t3;

		s0 = state[i + 0];
		s1 = state[i + 1];
		s2 = state[i + 2];
		s3 = state[i + 3];
		t0 = (s0 << 1) ^ (s0 << 2) ^ (s0 << 3)
			^ s1 ^ (s1 << 1) ^ (s1 << 3)
			^ s2 ^ (s2 << 2) ^ (s2 << 3)
			^ s3 ^ (s3 << 3);
		t1 = s0 ^ (s0 << 3)
			^ (s1 << 1) ^ (s1 << 2) ^ (s1 << 3)
			^ s2 ^ (s2 << 1) ^ (s2 << 3)
			^ s3 ^ (s3 << 2) ^ (s3 << 3);
		t2 = s0 ^ (s0 << 2) ^ (s0 << 3)
			^ s1 ^ (s1 << 3)
			^ (s2 << 1) ^ (s2 << 2) ^ (s2 << 3)
			^ s3 ^ (s3 << 1) ^ (s3 << 3);
		t3 = s0 ^ (s0 << 1) ^ (s0 << 3)
			^ s1 ^ (s1 << 2) ^ (s1 << 3)
			^ s2 ^ (s2 << 3)
			^ (s3 << 1) ^ (s3 << 2) ^ (s3 << 3);
		state[i + 0] = gf256red(t0);
		state[i + 1] = gf256red(t1);
		state[i + 2] = gf256red(t2);
		state[i + 3] = gf256red(t3);
	}
}