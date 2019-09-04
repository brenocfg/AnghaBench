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
typedef  unsigned long long int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int64_t
sign_extend(int64_t input, uint32_t sign_bit_index) 
{
	assert(sign_bit_index < 63);
	if (input & (1ULL << sign_bit_index)) {
		/* All 1's & ~[1's from 0 to sign bit] */
		input |= ((~0ULL) & ~((1ULL << (sign_bit_index + 1)) - 1ULL));
	}

	return input;
}