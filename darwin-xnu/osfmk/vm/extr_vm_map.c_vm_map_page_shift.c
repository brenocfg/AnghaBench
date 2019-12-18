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
 int VM_MAP_PAGE_SHIFT (int /*<<< orphan*/ ) ; 

int
vm_map_page_shift(
	vm_map_t map)
{
	return VM_MAP_PAGE_SHIFT(map);
}