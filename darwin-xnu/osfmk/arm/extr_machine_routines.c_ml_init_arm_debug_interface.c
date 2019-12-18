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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_debug_interface_map; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_debugid () ; 

void
ml_init_arm_debug_interface(
			    void * in_cpu_datap,
			    vm_offset_t virt_address)
{
	((cpu_data_t *)in_cpu_datap)->cpu_debug_interface_map = virt_address;
	do_debugid();
}