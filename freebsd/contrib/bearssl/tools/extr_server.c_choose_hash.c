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

__attribute__((used)) static unsigned
choose_hash(unsigned chashes)
{
	unsigned hash_id;

	for (hash_id = 6; hash_id >= 2; hash_id --) {
		if (((chashes >> hash_id) & 1) != 0) {
			return hash_id;
		}
	}
	/*
	 * Normally unreachable.
	 */
	return 0;
}