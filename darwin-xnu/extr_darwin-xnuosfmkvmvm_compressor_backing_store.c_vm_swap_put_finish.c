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
typedef  int /*<<< orphan*/  uint64_t ;
struct swapfile {scalar_t__ swp_io_count; int swp_flags; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int SWAP_WANTED ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_swap_put_failures ; 

kern_return_t
vm_swap_put_finish(struct swapfile *swf, uint64_t *f_offset, int error)
{
	lck_mtx_lock(&vm_swap_data_lock);

	swf->swp_io_count--;

	if ((swf->swp_flags & SWAP_WANTED) && swf->swp_io_count == 0) {
	
		swf->swp_flags &= ~SWAP_WANTED;
		thread_wakeup((event_t) &swf->swp_flags);
	}
	lck_mtx_unlock(&vm_swap_data_lock);

	if (error) {
		vm_swap_free(*f_offset);
		vm_swap_put_failures++;

		return KERN_FAILURE;
	}
	return KERN_SUCCESS;
}