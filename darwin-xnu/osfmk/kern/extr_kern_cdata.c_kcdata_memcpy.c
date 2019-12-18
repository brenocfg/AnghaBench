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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* kcdata_descriptor_t ;
struct TYPE_3__ {int kcd_flags; } ;

/* Variables and functions */
 int KCFLAG_USE_COPYOUT ; 
 int /*<<< orphan*/  KERN_NO_ACCESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ copyout (void const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 

kern_return_t kcdata_memcpy(kcdata_descriptor_t data, mach_vm_address_t dst_addr, const void *src_addr, uint32_t size)
{
	if (data->kcd_flags & KCFLAG_USE_COPYOUT) {
		if (copyout(src_addr, dst_addr, size))
			return KERN_NO_ACCESS;
	} else {
		memcpy((void *)dst_addr, src_addr, size);
	}
	return KERN_SUCCESS;
}