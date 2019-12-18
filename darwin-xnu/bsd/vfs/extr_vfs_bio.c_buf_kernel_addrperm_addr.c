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
 scalar_t__ buf_kernel_addrperm ; 

vm_offset_t
buf_kernel_addrperm_addr(void * addr)
{
	if ((vm_offset_t)addr == 0)
		return 0;
	else
		return ((vm_offset_t)addr + buf_kernel_addrperm);
}