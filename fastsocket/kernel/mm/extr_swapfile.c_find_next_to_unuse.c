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
struct swap_info_struct {unsigned int max; unsigned char* swap_map; } ;

/* Variables and functions */
 scalar_t__ SWAP_MAP_BAD ; 
 scalar_t__ swap_count (unsigned char) ; 

__attribute__((used)) static unsigned int find_next_to_unuse(struct swap_info_struct *si,
					unsigned int prev)
{
	unsigned int max = si->max;
	unsigned int i = prev;
	unsigned char count;

	/*
	 * No need for swap_lock here: we're just looking
	 * for whether an entry is in use, not modifying it; false
	 * hits are okay, and sys_swapoff() has already prevented new
	 * allocations from this area (while holding swap_lock).
	 */
	for (;;) {
		if (++i >= max) {
			if (!prev) {
				i = 0;
				break;
			}
			/*
			 * No entries in use at top of swap_map,
			 * loop back to start and recheck there.
			 */
			max = prev + 1;
			prev = 0;
			i = 1;
		}
		count = si->swap_map[i];
		if (count && swap_count(count) != SWAP_MAP_BAD)
			break;
	}
	return i;
}