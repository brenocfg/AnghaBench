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
typedef  int /*<<< orphan*/  vm_map_t ;

/* Variables and functions */

void
vm_map_set_jumbo(vm_map_t map)
{
#if defined (__arm64__)
	vm_map_set_max_addr(map, ~0);
#else /* arm64 */
	(void) map;
#endif
}