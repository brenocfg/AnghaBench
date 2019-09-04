#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
struct TYPE_3__ {int /*<<< orphan*/  vmmap_high_start; } ;

/* Variables and functions */

void
vm_map_set_high_start(
	vm_map_t	map,
	vm_map_offset_t	high_start)
{
	map->vmmap_high_start = high_start;
}