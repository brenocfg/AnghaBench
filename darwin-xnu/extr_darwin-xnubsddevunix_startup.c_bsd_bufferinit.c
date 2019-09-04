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

/* Variables and functions */
 int /*<<< orphan*/  bsd_startupearly () ; 
 int /*<<< orphan*/  bufinit () ; 

void
bsd_bufferinit(void)
{
#if SOCKETS
	kern_return_t   ret;
#endif
	/*
	 * Note: Console device initialized in kminit() from bsd_autoconf()
	 * prior to call to us in bsd_init().
	 */

	bsd_startupearly();

#if SOCKETS
	ret = kmem_suballoc(kernel_map,
			    (vm_offset_t *) &mbutl,
			    (vm_size_t) (nmbclusters * MCLBYTES),
			    FALSE,
			    VM_FLAGS_ANYWHERE,
			    VM_MAP_KERNEL_FLAGS_NONE,
			    VM_KERN_MEMORY_MBUF,
			    &mb_map);

	if (ret != KERN_SUCCESS)
		panic("Failed to allocate mb_map\n");
#endif /* SOCKETS */

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bufinit();
}