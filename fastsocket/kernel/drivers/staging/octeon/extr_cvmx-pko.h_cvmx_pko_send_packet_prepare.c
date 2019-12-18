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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  cvmx_wqe_t ;
typedef  scalar_t__ cvmx_pko_lock_t ;

/* Variables and functions */
 scalar_t__ CVMX_PKO_LOCK_ATOMIC_TAG ; 
 int /*<<< orphan*/  CVMX_POW_TAG_TYPE_ATOMIC ; 
 int CVMX_TAG_SUBGROUP_MASK ; 
 int CVMX_TAG_SUBGROUP_PKO ; 
 int CVMX_TAG_SUBGROUP_SHIFT ; 
 int CVMX_TAG_SW_BITS_INTERNAL ; 
 int CVMX_TAG_SW_SHIFT ; 
 scalar_t__ cvmx_phys_to_ptr (int) ; 
 int /*<<< orphan*/  cvmx_pow_tag_sw_full (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pko_send_packet_prepare(uint64_t port, uint64_t queue,
						cvmx_pko_lock_t use_locking)
{
	if (use_locking == CVMX_PKO_LOCK_ATOMIC_TAG) {
		/*
		 * Must do a full switch here to handle all cases.  We
		 * use a fake WQE pointer, as the POW does not access
		 * this memory.  The WQE pointer and group are only
		 * used if this work is descheduled, which is not
		 * supported by the
		 * cvmx_pko_send_packet_prepare/cvmx_pko_send_packet_finish
		 * combination.  Note that this is a special case in
		 * which these fake values can be used - this is not a
		 * general technique.
		 */
		uint32_t tag =
		    CVMX_TAG_SW_BITS_INTERNAL << CVMX_TAG_SW_SHIFT |
		    CVMX_TAG_SUBGROUP_PKO << CVMX_TAG_SUBGROUP_SHIFT |
		    (CVMX_TAG_SUBGROUP_MASK & queue);
		cvmx_pow_tag_sw_full((cvmx_wqe_t *) cvmx_phys_to_ptr(0x80), tag,
				     CVMX_POW_TAG_TYPE_ATOMIC, 0);
	}
}