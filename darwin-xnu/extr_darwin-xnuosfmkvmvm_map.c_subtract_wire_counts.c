#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int user_wired_count; int wired_count; scalar_t__ vme_start; scalar_t__ vme_end; } ;
struct TYPE_5__ {int /*<<< orphan*/  user_wire_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
subtract_wire_counts(
	vm_map_t	map,
	vm_map_entry_t	entry,
	boolean_t	user_wire)
{

	if (user_wire) {

		/*
		 * We're unwiring memory at the request of the user.  See if we're removing the last user wire reference.
		 */

		if (entry->user_wired_count == 1) {

			/*
			 * We're removing the last user wire reference.  Decrement the wired_count and the total
			 * user wired memory for this map.
			 */

			assert(entry->wired_count >= 1);
			entry->wired_count--;
			map->user_wire_size -= entry->vme_end - entry->vme_start;
		}

		assert(entry->user_wired_count >= 1);
		entry->user_wired_count--;

	} else {

		/*
		 * The kernel is unwiring the memory.   Just update the count.
		 */

		assert(entry->wired_count >= 1);
		entry->wired_count--;
	}
}