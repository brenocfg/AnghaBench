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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ user_size_t ;
typedef  scalar_t__ user_addr_t ;
typedef  int kern_return_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
#define  KERN_INVALID_ADDRESS 131 
#define  KERN_NO_SPACE 130 
#define  KERN_PROTECTION_FAILURE 129 
#define  KERN_SUCCESS 128 
 int /*<<< orphan*/  VM_KERN_MEMORY_BSD ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  current_map () ; 
 int /*<<< orphan*/  vm_map_page_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int vm_map_wire_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vslock(
	user_addr_t	addr,
	user_size_t	len)
{
	kern_return_t	kret;
	vm_map_t	map;

	map = current_map();
	kret = vm_map_wire_kernel(map,
			   vm_map_trunc_page(addr,
					     vm_map_page_mask(map)),
			   vm_map_round_page(addr+len,
					     vm_map_page_mask(map)), 
			   VM_PROT_READ | VM_PROT_WRITE, VM_KERN_MEMORY_BSD,
			   FALSE);

	switch (kret) {
	case KERN_SUCCESS:
		return (0);
	case KERN_INVALID_ADDRESS:
	case KERN_NO_SPACE:
		return (ENOMEM);
	case KERN_PROTECTION_FAILURE:
		return (EACCES);
	default:
		return (EINVAL);
	}
}