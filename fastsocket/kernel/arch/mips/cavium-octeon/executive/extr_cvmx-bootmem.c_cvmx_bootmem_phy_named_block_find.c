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
typedef  int uint32_t ;
struct cvmx_bootmem_named_block_desc {scalar_t__ size; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int major_version; unsigned int named_block_num_blocks; scalar_t__ minor_version; scalar_t__ named_block_name_len; int /*<<< orphan*/  named_block_array_addr; } ;

/* Variables and functions */
 int CVMX_BOOTMEM_FLAG_NO_LOCKING ; 
 TYPE_1__* cvmx_bootmem_desc ; 
 int /*<<< orphan*/  cvmx_bootmem_lock () ; 
 int /*<<< orphan*/  cvmx_bootmem_unlock () ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 

struct cvmx_bootmem_named_block_desc *
	cvmx_bootmem_phy_named_block_find(char *name, uint32_t flags)
{
	unsigned int i;
	struct cvmx_bootmem_named_block_desc *named_block_array_ptr;

#ifdef DEBUG
	cvmx_dprintf("cvmx_bootmem_phy_named_block_find: %s\n", name);
#endif
	/*
	 * Lock the structure to make sure that it is not being
	 * changed while we are examining it.
	 */
	if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_bootmem_lock();

	/* Use XKPHYS for 64 bit linux */
	named_block_array_ptr = (struct cvmx_bootmem_named_block_desc *)
	    cvmx_phys_to_ptr(cvmx_bootmem_desc->named_block_array_addr);

#ifdef DEBUG
	cvmx_dprintf
	    ("cvmx_bootmem_phy_named_block_find: named_block_array_ptr: %p\n",
	     named_block_array_ptr);
#endif
	if (cvmx_bootmem_desc->major_version == 3) {
		for (i = 0;
		     i < cvmx_bootmem_desc->named_block_num_blocks; i++) {
			if ((name && named_block_array_ptr[i].size
			     && !strncmp(name, named_block_array_ptr[i].name,
					 cvmx_bootmem_desc->named_block_name_len
					 - 1))
			    || (!name && !named_block_array_ptr[i].size)) {
				if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
					cvmx_bootmem_unlock();

				return &(named_block_array_ptr[i]);
			}
		}
	} else {
		cvmx_dprintf("ERROR: Incompatible bootmem descriptor "
			     "version: %d.%d at addr: %p\n",
			     (int)cvmx_bootmem_desc->major_version,
			     (int)cvmx_bootmem_desc->minor_version,
			     cvmx_bootmem_desc);
	}
	if (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_bootmem_unlock();

	return NULL;
}