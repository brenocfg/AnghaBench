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

/* Variables and functions */
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kfree (void*,scalar_t__) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_cs_blob_limit ; 

void
ubc_cs_blob_deallocate(
	vm_offset_t	blob_addr,
	vm_size_t	blob_size)
{
#if PMAP_CS
	if (blob_size > pmap_cs_blob_limit) {
		kmem_free(kernel_map, blob_addr, blob_size);
	} else
#endif
	{
		kfree((void *) blob_addr, blob_size);
	}
}