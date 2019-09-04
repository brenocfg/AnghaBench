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
struct swapout_io_completion {scalar_t__ swp_io_busy; } ;

/* Variables and functions */
 int VM_SWAPOUT_LIMIT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 struct swapout_io_completion* vm_swapout_ctx ; 
 int vm_swapout_soc_busy ; 

__attribute__((used)) static struct swapout_io_completion *
vm_swapout_find_free_soc(void)
{       int      i;

        for (i = 0; i < VM_SWAPOUT_LIMIT_MAX; i++) {
	        if (vm_swapout_ctx[i].swp_io_busy == 0)
		        return (&vm_swapout_ctx[i]);
	}
	assert(vm_swapout_soc_busy == VM_SWAPOUT_LIMIT_MAX);

	return NULL;
}