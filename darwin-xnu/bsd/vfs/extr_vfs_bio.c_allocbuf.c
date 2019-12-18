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
typedef  int /*<<< orphan*/  zone_t ;
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {uintptr_t b_datap; int b_bufsize; int b_bcount; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_META ; 
 int /*<<< orphan*/  B_ZALLOC ; 
 int /*<<< orphan*/  CLBYTES ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAXBSIZE ; 
 int MAXMETA ; 
 int /*<<< orphan*/  MINMETA ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_FILE ; 
 int /*<<< orphan*/  bcopy (void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getbufzone (int) ; 
 void* grab_memory_for_meta_buf (int) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_alloc_kobject (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 void* roundup (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

int
allocbuf(buf_t bp, int size)
{
	vm_size_t desired_size;

	desired_size = roundup(size, CLBYTES);

	if (desired_size < PAGE_SIZE)
		desired_size = PAGE_SIZE;
	if (desired_size > MAXBSIZE)
		panic("allocbuf: buffer larger than MAXBSIZE requested");

	if (ISSET(bp->b_flags, B_META)) {
		int    nsize = roundup(size, MINMETA);

		if (bp->b_datap) {
			vm_offset_t elem = (vm_offset_t)bp->b_datap;

			if (ISSET(bp->b_flags, B_ZALLOC)) {
			        if (bp->b_bufsize < nsize) {
				        zone_t zprev;

				        /* reallocate to a bigger size */

				        zprev = getbufzone(bp->b_bufsize);
					if (nsize <= MAXMETA) {
					        desired_size = nsize;

						/* b_datap not really a ptr */
						*(void **)(&bp->b_datap) = grab_memory_for_meta_buf(nsize);
					} else {
					        bp->b_datap = (uintptr_t)NULL;
					        kmem_alloc_kobject(kernel_map, (vm_offset_t *)&bp->b_datap, desired_size, VM_KERN_MEMORY_FILE);
						CLR(bp->b_flags, B_ZALLOC);
					}
					bcopy((void *)elem, (caddr_t)bp->b_datap, bp->b_bufsize);
					zfree(zprev, (void *)elem);
				} else {
				        desired_size = bp->b_bufsize;
				}

			} else {
				if ((vm_size_t)bp->b_bufsize < desired_size) {
					/* reallocate to a bigger size */
				        bp->b_datap = (uintptr_t)NULL;
					kmem_alloc_kobject(kernel_map, (vm_offset_t *)&bp->b_datap, desired_size, VM_KERN_MEMORY_FILE);
					bcopy((const void *)elem, (caddr_t)bp->b_datap, bp->b_bufsize);
					kmem_free(kernel_map, elem, bp->b_bufsize); 
				} else {
					desired_size = bp->b_bufsize;
				}
			}
		} else {
			/* new allocation */
			if (nsize <= MAXMETA) {
				desired_size = nsize;

				/* b_datap not really a ptr */
				*(void **)(&bp->b_datap) = grab_memory_for_meta_buf(nsize);
				SET(bp->b_flags, B_ZALLOC);
			} else
				kmem_alloc_kobject(kernel_map, (vm_offset_t *)&bp->b_datap, desired_size, VM_KERN_MEMORY_FILE);
		}

		if (bp->b_datap == 0)
		        panic("allocbuf: NULL b_datap");
	}
	bp->b_bufsize = desired_size;
	bp->b_bcount = size;

	return (0);
}