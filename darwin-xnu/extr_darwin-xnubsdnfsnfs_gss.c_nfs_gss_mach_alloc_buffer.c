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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int /*<<< orphan*/ * vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ vm_allocate_kernel (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vm_map_page_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_wire_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_gss_mach_alloc_buffer(u_char *buf, uint32_t buflen, vm_map_copy_t *addr)
{
	kern_return_t kr;
	vm_offset_t kmem_buf;
	vm_size_t tbuflen;

	*addr = NULL;
	if (buf == NULL || buflen == 0)
		return;

	tbuflen = vm_map_round_page(buflen,
				    vm_map_page_mask(ipc_kernel_map));
	kr = vm_allocate_kernel(ipc_kernel_map, &kmem_buf, tbuflen, VM_FLAGS_ANYWHERE, VM_KERN_MEMORY_FILE);
	if (kr != 0) {
		printf("nfs_gss_mach_alloc_buffer: vm_allocate failed\n");
		return;
	}

	kr = vm_map_wire_kernel(ipc_kernel_map,
			 vm_map_trunc_page(kmem_buf,
					   vm_map_page_mask(ipc_kernel_map)),
			 vm_map_round_page(kmem_buf + tbuflen,
					   vm_map_page_mask(ipc_kernel_map)),
		VM_PROT_READ|VM_PROT_WRITE, VM_KERN_MEMORY_FILE, FALSE);
	if (kr != 0) {
		printf("nfs_gss_mach_alloc_buffer: vm_map_wire failed\n");
		return;
	}
	
	bcopy(buf, (void *) kmem_buf, buflen);
	// Shouldn't need to bzero below since vm_allocate returns zeroed pages
	// bzero(kmem_buf + buflen, tbuflen - buflen);
	
	kr = vm_map_unwire(ipc_kernel_map,
			   vm_map_trunc_page(kmem_buf,
					     vm_map_page_mask(ipc_kernel_map)),
			   vm_map_round_page(kmem_buf + tbuflen,
					     vm_map_page_mask(ipc_kernel_map)),
			   FALSE);
	if (kr != 0) {
		printf("nfs_gss_mach_alloc_buffer: vm_map_unwire failed\n");
		return;
	}

	kr = vm_map_copyin(ipc_kernel_map, (vm_map_address_t) kmem_buf,
		(vm_map_size_t) buflen, TRUE, addr);
	if (kr != 0) {
		printf("nfs_gss_mach_alloc_buffer: vm_map_copyin failed\n");
		return;
	}
}