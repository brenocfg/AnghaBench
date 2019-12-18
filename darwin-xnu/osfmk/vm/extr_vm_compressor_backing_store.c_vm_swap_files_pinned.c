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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int TRUE ; 
 scalar_t__ vm_num_pinned_swap_files ; 
 scalar_t__ vm_num_swap_files ; 
 scalar_t__ vm_swappin_enabled ; 

boolean_t
vm_swap_files_pinned(void)
{
        boolean_t result;

	if (vm_swappin_enabled == FALSE)
		return (TRUE);

        result = (vm_num_pinned_swap_files == vm_num_swap_files);

        return (result);
}