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
typedef  int uint64_t ;

/* Variables and functions */
 int VM_MAP_PAGE_SHIFT (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_is_64bit (int /*<<< orphan*/ ) ; 

uint64_t
vm_map_get_max_loader_aslr_slide_pages(vm_map_t map)
{
#if defined(__arm64__)
	/* We limit the loader slide to 4MB, in order to ensure at least 8 bits
	 * of independent entropy on 16KB page systems.
	 */
	return (1 << (22 - VM_MAP_PAGE_SHIFT(map)));
#else
	return (1 << (vm_map_is_64bit(map) ? 16 : 8));
#endif
}