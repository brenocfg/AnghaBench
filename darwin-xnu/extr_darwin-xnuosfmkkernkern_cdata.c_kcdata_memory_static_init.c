#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kcdata_descriptor {int dummy; } ;
typedef  void* mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* kcdata_descriptor_t ;
struct TYPE_5__ {unsigned int kcd_flags; unsigned int kcd_length; void* kcd_addr_end; void* kcd_addr_begin; } ;

/* Variables and functions */
 unsigned int KCFLAG_USE_COPYOUT ; 
 unsigned int KCFLAG_USE_MEMCOPY ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kcdata_get_memory_addr (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,void**) ; 

kern_return_t kcdata_memory_static_init(kcdata_descriptor_t data, mach_vm_address_t buffer_addr_p, unsigned data_type, unsigned size, unsigned flags)
{
	mach_vm_address_t user_addr = 0;

	if (data == NULL) {
		return KERN_INVALID_ARGUMENT;
	}
	bzero(data, sizeof(struct kcdata_descriptor));
	data->kcd_addr_begin = buffer_addr_p;
	data->kcd_addr_end = buffer_addr_p;
	data->kcd_flags = (flags & KCFLAG_USE_COPYOUT)? KCFLAG_USE_COPYOUT : KCFLAG_USE_MEMCOPY;
	data->kcd_length = size;

	/* Initialize the BEGIN header */
	return kcdata_get_memory_addr(data, data_type, 0, &user_addr);
}