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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int CONFIG_CAVIUM_RESERVE32 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ USE_32BIT_SHARED ; 
 char* cvmx_bootmem_alloc_range (int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_fpa_free (char*,int,int /*<<< orphan*/ ) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 
 int /*<<< orphan*/  pr_notice (char*,char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cvm_oct_fill_hw_memory(int pool, int size, int elements)
{
	char *memory;
	int freed = elements;

	if (USE_32BIT_SHARED) {
		extern uint64_t octeon_reserve32_memory;

		memory =
		    cvmx_bootmem_alloc_range(elements * size, 128,
					     octeon_reserve32_memory,
					     octeon_reserve32_memory +
					     (CONFIG_CAVIUM_RESERVE32 << 20) -
					     1);
		if (memory == NULL)
			panic("Unable to allocate %u bytes for FPA pool %d\n",
			      elements * size, pool);

		pr_notice("Memory range %p - %p reserved for "
			  "hardware\n", memory,
			  memory + elements * size - 1);

		while (freed) {
			cvmx_fpa_free(memory, pool, 0);
			memory += size;
			freed--;
		}
	} else {
		while (freed) {
			/* We need to force alignment to 128 bytes here */
			memory = kmalloc(size + 127, GFP_ATOMIC);
			if (unlikely(memory == NULL)) {
				pr_warning("Unable to allocate %u bytes for "
					   "FPA pool %d\n",
				     elements * size, pool);
				break;
			}
			memory = (char *)(((unsigned long)memory + 127) & -128);
			cvmx_fpa_free(memory, pool, 0);
			freed--;
		}
	}
	return elements - freed;
}