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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_multihash_context ; 
 size_t offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_32 ; 
 int /*<<< orphan*/  val_64 ; 

__attribute__((used)) static size_t
get_state_offset(int id)
{
	if (id >= 5) {
		/*
		 * SHA-384 has id 5, and SHA-512 has id 6. Both use
		 * eight 64-bit words for their state.
		 */
		return offsetof(br_multihash_context, val_64)
			+ ((size_t)(id - 5) * (8 * sizeof(uint64_t)));
	} else {
		/*
		 * MD5 has id 1, SHA-1 has id 2, SHA-224 has id 3 and
		 * SHA-256 has id 4. They use 32-bit words for their
		 * states (4 words for MD5, 5 for SHA-1, 8 for SHA-224
		 * and 8 for SHA-256).
		 */
		unsigned x;

		x = id - 1;
		x = ((x + (x & (x >> 1))) << 2) + (x >> 1);
		return offsetof(br_multihash_context, val_32)
			+ x * sizeof(uint32_t);
	}
}