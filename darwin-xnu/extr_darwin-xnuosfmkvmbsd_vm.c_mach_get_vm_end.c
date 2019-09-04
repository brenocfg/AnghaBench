#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/  vme_end; } ;

/* Variables and functions */
 TYPE_1__* vm_map_last_entry (int /*<<< orphan*/ ) ; 

mach_vm_offset_t
mach_get_vm_end(vm_map_t map)
{
	return( vm_map_last_entry(map)->vme_end);
}