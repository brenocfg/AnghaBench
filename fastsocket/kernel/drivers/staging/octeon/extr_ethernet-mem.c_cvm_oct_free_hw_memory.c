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
 scalar_t__ USE_32BIT_SHARED ; 
 char* cvmx_fpa_alloc (int) ; 
 int /*<<< orphan*/  cvmx_ptr_to_phys (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

__attribute__((used)) static void cvm_oct_free_hw_memory(int pool, int size, int elements)
{
	if (USE_32BIT_SHARED) {
		pr_warning("Warning: 32 shared memory is not freeable\n");
	} else {
		char *memory;
		do {
			memory = cvmx_fpa_alloc(pool);
			if (memory) {
				elements--;
				kfree(phys_to_virt(cvmx_ptr_to_phys(memory)));
			}
		} while (memory);

		if (elements < 0)
			pr_warning("Freeing of pool %u had too many "
				   "buffers (%d)\n",
			       pool, elements);
		else if (elements > 0)
			pr_warning("Warning: Freeing of pool %u is "
				"missing %d buffers\n",
			     pool, elements);
	}
}