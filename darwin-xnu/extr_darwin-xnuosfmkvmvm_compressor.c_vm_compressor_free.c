#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* c_slot_mapping_t ;
struct TYPE_3__ {scalar_t__ s_cseg; int /*<<< orphan*/  s_cindx; } ;

/* Variables and functions */
 int C_DONT_BLOCK ; 
 scalar_t__ C_SV_CSEG_ID ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int c_decompress_page (int /*<<< orphan*/ *,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  c_segment_pages_compressed ; 
 int /*<<< orphan*/  c_segment_sv_hash_drop_ref (int /*<<< orphan*/ ) ; 

int
vm_compressor_free(int *slot, int flags)
{
	c_slot_mapping_t  slot_ptr;
	int	zeroslot = 1;
	int	retval;

	assert(flags == 0 || flags == C_DONT_BLOCK);

	slot_ptr = (c_slot_mapping_t)slot;

	if (slot_ptr->s_cseg == C_SV_CSEG_ID) {

		c_segment_sv_hash_drop_ref(slot_ptr->s_cindx);
		OSAddAtomic(-1, &c_segment_pages_compressed);

		*slot = 0;
		return (0);
	}
	retval = c_decompress_page(NULL, slot_ptr, flags, &zeroslot);
	/*
	 * returns 0 if we successfully freed the specified compressed page
	 * returns -2 if (flags & C_DONT_BLOCK) and we found 'c_busy' set
	 */

	if (retval == 0)
		*slot = 0;
	else
		assert(retval == -2);

	return (retval);
}