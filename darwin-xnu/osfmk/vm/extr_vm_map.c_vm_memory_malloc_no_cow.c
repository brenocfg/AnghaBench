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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int vm_memory_malloc_no_cow_mask ; 

__attribute__((used)) static boolean_t
vm_memory_malloc_no_cow(
	int alias)
{
	uint64_t alias_mask;

	alias_mask = 1ULL << alias;
	if (alias_mask & vm_memory_malloc_no_cow_mask) {
		return TRUE;
	}
	return FALSE;
}