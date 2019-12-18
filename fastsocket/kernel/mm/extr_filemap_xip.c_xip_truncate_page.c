#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct address_space {TYPE_2__* a_ops; TYPE_1__* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_4__ {int (* get_xip_mem ) (struct address_space*,int,int /*<<< orphan*/ ,void**,unsigned long*) ;} ;
struct TYPE_3__ {int i_blkbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODATA ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct address_space*,int,int /*<<< orphan*/ ,void**,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

int
xip_truncate_page(struct address_space *mapping, loff_t from)
{
	pgoff_t index = from >> PAGE_CACHE_SHIFT;
	unsigned offset = from & (PAGE_CACHE_SIZE-1);
	unsigned blocksize;
	unsigned length;
	void *xip_mem;
	unsigned long xip_pfn;
	int err;

	BUG_ON(!mapping->a_ops->get_xip_mem);

	blocksize = 1 << mapping->host->i_blkbits;
	length = offset & (blocksize - 1);

	/* Block boundary? Nothing to do */
	if (!length)
		return 0;

	length = blocksize - length;

	err = mapping->a_ops->get_xip_mem(mapping, index, 0,
						&xip_mem, &xip_pfn);
	if (unlikely(err)) {
		if (err == -ENODATA)
			/* Hole? No need to truncate */
			return 0;
		else
			return err;
	}
	memset(xip_mem + offset, 0, length);
	return 0;
}