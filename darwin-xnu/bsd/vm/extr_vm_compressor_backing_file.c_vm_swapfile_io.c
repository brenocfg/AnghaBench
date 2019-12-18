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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * upl_t ;
typedef  scalar_t__ upl_size_t ;
typedef  int upl_control_flags_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int FALSE ; 
 int IO_NOCACHE ; 
 int IO_NODELOCKED ; 
 int IO_SWAP_DISPATCH ; 
 int IO_SYNC ; 
 int IO_UNIT ; 
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_SIZE_64 ; 
 int SWAP_READ ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int UPL_COPYOUT_FROM ; 
 int UPL_IGNORE_VALID_PAGE_CHECK ; 
 int UPL_IOSYNC ; 
 int UPL_PAGING_ENCRYPTED ; 
 int UPL_SET_INTERNAL ; 
 int UPL_SET_LITE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_OSFMK ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  upl_set_iodone (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_create_upl (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned int*,int*,int /*<<< orphan*/ ) ; 
 int vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_pagein (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  vnode_pageout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int*) ; 

int
vm_swapfile_io(vnode_t vp, uint64_t offset, uint64_t start, int npages, int flags, void *upl_iodone)
{
	int error = 0;
	uint64_t io_size = npages * PAGE_SIZE_64;
#if 1
	kern_return_t	kr = KERN_SUCCESS;
	upl_t		upl = NULL;
	unsigned int	count = 0;
	upl_control_flags_t upl_create_flags = 0;
	int		upl_control_flags = 0;
	upl_size_t	upl_size = 0;

	upl_create_flags = UPL_SET_INTERNAL | UPL_SET_LITE;

	if (upl_iodone == NULL)
	        upl_control_flags = UPL_IOSYNC;

#if ENCRYPTED_SWAP
	upl_control_flags |= UPL_PAGING_ENCRYPTED;
#endif

	if ((flags & SWAP_READ) == FALSE) {
		upl_create_flags |= UPL_COPYOUT_FROM;
	}
 
	upl_size = io_size;
	kr = vm_map_create_upl( kernel_map,
				start,
				&upl_size,
				&upl,
				NULL,
				&count,
				&upl_create_flags,
				VM_KERN_MEMORY_OSFMK);

	if (kr != KERN_SUCCESS || (upl_size != io_size)) {
		panic("vm_map_create_upl failed with %d\n", kr);
	}

	if (flags & SWAP_READ) {
		vnode_pagein(vp,
			      upl,
			      0,
			      offset,
			      io_size,
			      upl_control_flags | UPL_IGNORE_VALID_PAGE_CHECK,
			      &error);
		if (error) {
#if DEBUG
			printf("vm_swapfile_io: vnode_pagein failed with %d (vp: %p, offset: 0x%llx, size:%llu)\n", error, vp, offset, io_size);
#else /* DEBUG */
			printf("vm_swapfile_io: vnode_pagein failed with %d.\n", error);
#endif /* DEBUG */
		}
	
	} else {
	        upl_set_iodone(upl, upl_iodone);

		vnode_pageout(vp,
			      upl,
			      0,
			      offset,
			      io_size,
			      upl_control_flags,
			      &error);
		if (error) {
#if DEBUG
			printf("vm_swapfile_io: vnode_pageout failed with %d (vp: %p, offset: 0x%llx, size:%llu)\n", error, vp, offset, io_size);
#else /* DEBUG */
			printf("vm_swapfile_io: vnode_pageout failed with %d.\n", error);
#endif /* DEBUG */
		}
	}
	return error;

#else /* 1 */
	vfs_context_t ctx;
	ctx = vfs_context_kernel();
		
	error = vn_rdwr((flags & SWAP_READ) ? UIO_READ : UIO_WRITE, vp, (caddr_t)start, io_size, offset,
		UIO_SYSSPACE, IO_SYNC | IO_NODELOCKED | IO_UNIT | IO_NOCACHE | IO_SWAP_DISPATCH, vfs_context_ucred(ctx), (int *) 0, vfs_context_proc(ctx));

	if (error) {
		printf("vn_rdwr: Swap I/O failed with %d\n", error);
	}
	return error;
#endif /* 1 */
}