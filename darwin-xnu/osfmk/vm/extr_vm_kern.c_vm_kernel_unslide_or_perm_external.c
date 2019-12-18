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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_kernel_addrperm_external (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
vm_kernel_unslide_or_perm_external(
	vm_offset_t addr,
	vm_offset_t *up_addr)
{
	vm_kernel_addrperm_external(addr, up_addr);
}