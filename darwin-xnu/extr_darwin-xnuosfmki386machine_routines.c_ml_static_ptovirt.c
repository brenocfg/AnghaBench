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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 unsigned long VM_MIN_KERNEL_ADDRESS ; 

vm_offset_t
ml_static_ptovirt(
	vm_offset_t paddr)
{
#if defined(__x86_64__)
	return (vm_offset_t)(((unsigned long) paddr) | VM_MIN_KERNEL_ADDRESS);
#else
	return (vm_offset_t)((paddr) | LINEAR_KERNEL_ADDRESS);
#endif
}