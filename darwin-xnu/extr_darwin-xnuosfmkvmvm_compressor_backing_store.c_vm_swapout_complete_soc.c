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
struct swapout_io_completion {scalar_t__ swp_io_busy; scalar_t__ swp_io_done; int /*<<< orphan*/  swp_c_size; int /*<<< orphan*/  swp_f_offset; int /*<<< orphan*/  swp_c_seg; scalar_t__ swp_io_error; int /*<<< orphan*/  swp_swf; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  c_list_lock ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swap_put_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vm_swapout_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swapout_soc_busy ; 
 int /*<<< orphan*/  vm_swapout_soc_done ; 

__attribute__((used)) static void
vm_swapout_complete_soc(struct swapout_io_completion *soc)
{
        kern_return_t  kr;

        if (soc->swp_io_error)
	        kr = KERN_FAILURE;
	else
	        kr = KERN_SUCCESS;

	lck_mtx_unlock_always(c_list_lock);

	vm_swap_put_finish(soc->swp_swf, &soc->swp_f_offset, soc->swp_io_error);
	vm_swapout_finish(soc->swp_c_seg, soc->swp_f_offset, soc->swp_c_size, kr);

	lck_mtx_lock_spin_always(c_list_lock);

	soc->swp_io_done = 0;
	soc->swp_io_busy = 0;

	vm_swapout_soc_busy--;
	vm_swapout_soc_done--;
}