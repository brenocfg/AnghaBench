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
 void vm_kernel_addrhash_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_kernel_addrhash_salt_ext ; 

void
vm_kernel_addrhash_external(
	vm_offset_t addr,
	vm_offset_t *hash_addr)
{
	return vm_kernel_addrhash_internal(addr, hash_addr, vm_kernel_addrhash_salt_ext);
}