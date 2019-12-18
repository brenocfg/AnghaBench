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

__attribute__((used)) static void
mix_columns(unsigned *state)
{
	int i;

	for (i = 0; i < 16; i += 4) {
		unsigned s0, s1, s2, s3;
		unsigned t0, t1, t2, t3;

		s0 = state[i + 0];
		s1 = state[i + 1];
		s2 = state[i + 2];
		s3 = state[i + 3];
		t0 = (s0 << 1) ^ s1 ^ (s1 << 1) ^ s2 ^ s3;
		t1 = s0 ^ (s1 << 1) ^ s2 ^ (s2 << 1) ^ s3;
		t2 = s0 ^ s1 ^ (s2 << 1) ^ s3 ^ (s3 << 1);
		t3 = s0 ^ (s0 << 1) ^ s1 ^ s2 ^ (s3 << 1);
		state[i + 0] = t0 ^ ((unsigned)(-(int)(t0 >> 8)) & 0x11B);
		state[i + 1] = t1 ^ ((unsigned)(-(int)(t1 >> 8)) & 0x11B);
		state[i + 2] = t2 ^ ((unsigned)(-(int)(t2 >> 8)) & 0x11B);
		state[i + 3] = t3 ^ ((unsigned)(-(int)(t3 >> 8)) & 0x11B);
	}
}