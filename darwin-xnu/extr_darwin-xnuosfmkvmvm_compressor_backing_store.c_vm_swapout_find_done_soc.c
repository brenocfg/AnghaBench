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
struct swapout_io_completion {scalar_t__ swp_io_done; } ;

/* Variables and functions */
 int VM_SWAPOUT_LIMIT_MAX ; 
 struct swapout_io_completion* vm_swapout_ctx ; 
 scalar_t__ vm_swapout_soc_done ; 

__attribute__((used)) static struct swapout_io_completion *
vm_swapout_find_done_soc(void)
{       int      i;

        if (vm_swapout_soc_done) {
	        for (i = 0; i < VM_SWAPOUT_LIMIT_MAX; i++) {
		        if (vm_swapout_ctx[i].swp_io_done)
			        return (&vm_swapout_ctx[i]);
		}
	}
	return NULL;
}