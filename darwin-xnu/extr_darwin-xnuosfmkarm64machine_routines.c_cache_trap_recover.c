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
typedef  int /*<<< orphan*/  vm_map_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  cache_trap_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 

__attribute__((used)) static void
cache_trap_recover()
{
	vm_map_address_t fault_addr;

	__asm__ volatile("mrs %0, FAR_EL1" : "=r"(fault_addr));

	cache_trap_error(current_thread(), fault_addr);
}