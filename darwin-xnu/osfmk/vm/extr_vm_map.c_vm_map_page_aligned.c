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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  scalar_t__ offset ;
typedef  int boolean_t ;

/* Variables and functions */

boolean_t
vm_map_page_aligned(
	vm_map_offset_t	offset,
	vm_map_offset_t	mask)
{
	return ((offset) & mask) == 0;
}