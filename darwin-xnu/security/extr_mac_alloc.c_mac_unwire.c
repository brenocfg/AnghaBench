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
 int /*<<< orphan*/  CAST_USER_ADDR_T (void*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  kalloc_map ; 
 int vm_map_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mac_unwire(void *start, void *end)
{

	return (vm_map_unwire(kalloc_map, CAST_USER_ADDR_T(start),
		CAST_USER_ADDR_T(end), FALSE));
}