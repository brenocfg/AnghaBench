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
struct trim_list {int tl_offset; struct trim_list* tl_next; } ;
struct swapfile {int* swp_bitmap; unsigned int swp_free_hint; int /*<<< orphan*/  swp_nseginuse; int /*<<< orphan*/ ** swp_csegs; int /*<<< orphan*/  swp_vp; scalar_t__ swp_delayed_trim_count; struct trim_list* swp_delayed_trim_list_head; } ;

/* Variables and functions */
 int COMPRESSED_SWAP_CHUNK_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kfree (struct trim_list*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_swap_data_lock ; 
 int /*<<< orphan*/  vm_swapfile_total_segs_used ; 
 int /*<<< orphan*/  vnode_trim_list (int /*<<< orphan*/ ,struct trim_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_swap_do_delayed_trim(struct swapfile *swf)
{
	struct trim_list *tl, *tl_head;

	lck_mtx_lock(&vm_swap_data_lock);

	tl_head = swf->swp_delayed_trim_list_head;
	swf->swp_delayed_trim_list_head = NULL;
	swf->swp_delayed_trim_count = 0;

	lck_mtx_unlock(&vm_swap_data_lock);

	vnode_trim_list(swf->swp_vp, tl_head, TRUE);
	
	while ((tl = tl_head) != NULL) {
		unsigned int	segidx = 0;
		unsigned int	byte_for_segidx = 0;
		unsigned int	offset_within_byte = 0;

		lck_mtx_lock(&vm_swap_data_lock);

		segidx = (unsigned int) (tl->tl_offset / COMPRESSED_SWAP_CHUNK_SIZE);
			
		byte_for_segidx = segidx >> 3;
		offset_within_byte = segidx % 8;

		if ((swf->swp_bitmap)[byte_for_segidx] & (1 << offset_within_byte)) {
				
			(swf->swp_bitmap)[byte_for_segidx] &= ~(1 << offset_within_byte);
			
			swf->swp_csegs[segidx] = NULL;

			swf->swp_nseginuse--;
			vm_swapfile_total_segs_used--;

			if (segidx < swf->swp_free_hint) {
				swf->swp_free_hint = segidx;
			}
		}
		lck_mtx_unlock(&vm_swap_data_lock);

		tl_head = tl->tl_next;

		kfree(tl, sizeof(struct trim_list));
	}		
}