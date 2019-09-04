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
 int /*<<< orphan*/  vm_page_wire_count ; 
 int /*<<< orphan*/  vm_page_wire_count_on_boot ; 

void
vm_init_before_launchd()
{
	vm_page_wire_count_on_boot = vm_page_wire_count;
}