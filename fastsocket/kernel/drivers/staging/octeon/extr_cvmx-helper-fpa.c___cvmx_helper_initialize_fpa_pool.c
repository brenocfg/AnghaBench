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

/* Variables and functions */
 int CVMX_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_QUEX_AVAILABLE (int) ; 
 void* cvmx_bootmem_alloc (int,int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,char const*,...) ; 
 int /*<<< orphan*/  cvmx_fpa_setup_pool (int,char const*,void*,int,int) ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cvmx_helper_initialize_fpa_pool(int pool, uint64_t buffer_size,
					     uint64_t buffers, const char *name)
{
	uint64_t current_num;
	void *memory;
	uint64_t align = CVMX_CACHE_LINE_SIZE;

	/*
	 * Align the allocation so that power of 2 size buffers are
	 * naturally aligned.
	 */
	while (align < buffer_size)
		align = align << 1;

	if (buffers == 0)
		return 0;

	current_num = cvmx_read_csr(CVMX_FPA_QUEX_AVAILABLE(pool));
	if (current_num) {
		cvmx_dprintf("Fpa pool %d(%s) already has %llu buffers. "
			     "Skipping setup.\n",
		     pool, name, (unsigned long long)current_num);
		return 0;
	}

	memory = cvmx_bootmem_alloc(buffer_size * buffers, align);
	if (memory == NULL) {
		cvmx_dprintf("Out of memory initializing fpa pool %d(%s).\n",
			     pool, name);
		return -1;
	}
	cvmx_fpa_setup_pool(pool, name, memory, buffer_size, buffers);
	return 0;
}