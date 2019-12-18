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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* kcdata_descriptor_t ;
struct TYPE_3__ {int kcd_flags; } ;

/* Variables and functions */
 int KCFLAG_USE_COPYOUT ; 
 int /*<<< orphan*/  KERN_NO_ACCESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  bzero (void*,scalar_t__) ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ **,scalar_t__,scalar_t__) ; 

kern_return_t
kcdata_bzero(kcdata_descriptor_t data, mach_vm_address_t dst_addr, uint32_t size)
{
	kern_return_t kr = KERN_SUCCESS;
	if (data->kcd_flags & KCFLAG_USE_COPYOUT) {
		uint8_t zeros[16] = {};
		while (size) {
			uint32_t block_size = MIN(size, 16);
			kr = copyout(&zeros, dst_addr, block_size);
			if (kr)
				return KERN_NO_ACCESS;
			size -= block_size;
		}
		return KERN_SUCCESS;
	} else {
		bzero((void*)dst_addr, size);
		return KERN_SUCCESS;
	}
}