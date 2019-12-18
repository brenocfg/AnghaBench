#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int major_version; scalar_t__ head_addr; scalar_t__ minor_version; } ;

/* Variables and functions */
 int CVMX_BOOTMEM_FLAG_NO_LOCKING ; 
 TYPE_1__* cvmx_bootmem_desc ; 
 int /*<<< orphan*/  cvmx_bootmem_lock () ; 
 scalar_t__ cvmx_bootmem_phy_get_next (scalar_t__) ; 
 scalar_t__ cvmx_bootmem_phy_get_size (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_set_next (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_set_size (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_bootmem_unlock () ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int,...) ; 

int __cvmx_bootmem_phy_free(uint64_t phy_addr, uint64_t size, uint32_t flags)
{
	uint64_t cur_addr;
	uint64_t prev_addr = 0;	/* zero is invalid */
	int retval = 0;

#ifdef DEBUG
	cvmx_dprintf("__cvmx_bootmem_phy_free addr: 0x%llx, size: 0x%llx\n",
		     (unsigned long long)phy_addr, (unsigned long long)size);
#endif
	if (cvmx_bootmem_desc->major_version > 3) {
		cvmx_dprintf("ERROR: Incompatible bootmem descriptor "
			     "version: %d.%d at addr: %p\n",
			     (int)cvmx_bootmem_desc->major_version,
			     (int)cvmx_bootmem_desc->minor_version,
			     cvmx_bootmem_desc);
		return 0;
	}

	/* 0 is not a valid size for this allocator */
	if (!size)
		return 0;

	if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_bootmem_lock();
	cur_addr = cvmx_bootmem_desc->head_addr;
	if (cur_addr == 0 || phy_addr < cur_addr) {
		/* add at front of list - special case with changing head ptr */
		if (cur_addr && phy_addr + size > cur_addr)
			goto bootmem_free_done;	/* error, overlapping section */
		else if (phy_addr + size == cur_addr) {
			/* Add to front of existing first block */
			cvmx_bootmem_phy_set_next(phy_addr,
						  cvmx_bootmem_phy_get_next
						  (cur_addr));
			cvmx_bootmem_phy_set_size(phy_addr,
						  cvmx_bootmem_phy_get_size
						  (cur_addr) + size);
			cvmx_bootmem_desc->head_addr = phy_addr;

		} else {
			/* New block before first block.  OK if cur_addr is 0 */
			cvmx_bootmem_phy_set_next(phy_addr, cur_addr);
			cvmx_bootmem_phy_set_size(phy_addr, size);
			cvmx_bootmem_desc->head_addr = phy_addr;
		}
		retval = 1;
		goto bootmem_free_done;
	}

	/* Find place in list to add block */
	while (cur_addr && phy_addr > cur_addr) {
		prev_addr = cur_addr;
		cur_addr = cvmx_bootmem_phy_get_next(cur_addr);
	}

	if (!cur_addr) {
		/*
		 * We have reached the end of the list, add on to end,
		 * checking to see if we need to combine with last
		 * block
		 */
		if (prev_addr + cvmx_bootmem_phy_get_size(prev_addr) ==
		    phy_addr) {
			cvmx_bootmem_phy_set_size(prev_addr,
						  cvmx_bootmem_phy_get_size
						  (prev_addr) + size);
		} else {
			cvmx_bootmem_phy_set_next(prev_addr, phy_addr);
			cvmx_bootmem_phy_set_size(phy_addr, size);
			cvmx_bootmem_phy_set_next(phy_addr, 0);
		}
		retval = 1;
		goto bootmem_free_done;
	} else {
		/*
		 * insert between prev and cur nodes, checking for
		 * merge with either/both.
		 */
		if (prev_addr + cvmx_bootmem_phy_get_size(prev_addr) ==
		    phy_addr) {
			/* Merge with previous */
			cvmx_bootmem_phy_set_size(prev_addr,
						  cvmx_bootmem_phy_get_size
						  (prev_addr) + size);
			if (phy_addr + size == cur_addr) {
				/* Also merge with current */
				cvmx_bootmem_phy_set_size(prev_addr,
					cvmx_bootmem_phy_get_size(cur_addr) +
					cvmx_bootmem_phy_get_size(prev_addr));
				cvmx_bootmem_phy_set_next(prev_addr,
					cvmx_bootmem_phy_get_next(cur_addr));
			}
			retval = 1;
			goto bootmem_free_done;
		} else if (phy_addr + size == cur_addr) {
			/* Merge with current */
			cvmx_bootmem_phy_set_size(phy_addr,
						  cvmx_bootmem_phy_get_size
						  (cur_addr) + size);
			cvmx_bootmem_phy_set_next(phy_addr,
						  cvmx_bootmem_phy_get_next
						  (cur_addr));
			cvmx_bootmem_phy_set_next(prev_addr, phy_addr);
			retval = 1;
			goto bootmem_free_done;
		}

		/* It is a standalone block, add in between prev and cur */
		cvmx_bootmem_phy_set_size(phy_addr, size);
		cvmx_bootmem_phy_set_next(phy_addr, cur_addr);
		cvmx_bootmem_phy_set_next(prev_addr, phy_addr);

	}
	retval = 1;

bootmem_free_done:
	if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_bootmem_unlock();
	return retval;

}