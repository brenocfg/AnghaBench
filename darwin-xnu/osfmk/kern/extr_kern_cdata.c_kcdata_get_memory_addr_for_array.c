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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  kcdata_descriptor_t ;

/* Variables and functions */
 int KCDATA_TYPE_ARRAY_PAD0 ; 
 int kcdata_calc_padding (int) ; 
 int /*<<< orphan*/  kcdata_get_memory_addr_with_flavor (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 

kern_return_t kcdata_get_memory_addr_for_array(
		kcdata_descriptor_t data,
		uint32_t type_of_element,
		uint32_t size_of_element,
		uint32_t count,
		mach_vm_address_t *user_addr)
{
	/* for arrays we record the number of padding bytes as the low-order 4 bits
	 * of the type field.  KCDATA_TYPE_ARRAY_PAD{x} means x bytes of pad. */
	uint64_t flags      = type_of_element;
	flags               = (flags << 32) | count;
	uint32_t total_size = count * size_of_element;
	uint32_t pad        = kcdata_calc_padding(total_size);

	return kcdata_get_memory_addr_with_flavor(data, KCDATA_TYPE_ARRAY_PAD0 | pad, total_size, flags, user_addr);
}