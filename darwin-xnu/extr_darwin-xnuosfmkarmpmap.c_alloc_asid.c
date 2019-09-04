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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 unsigned int ARM_MAX_ASID ; 
 int MAX_ASID ; 
 int NBBY ; 
 int* asid_bitmap ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int ffs (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmaps_lock ; 

__attribute__((used)) static unsigned int
alloc_asid(
	void)
{
	unsigned int    asid_bitmap_index;

	pmap_simple_lock(&pmaps_lock);
	for (asid_bitmap_index = 0; asid_bitmap_index < (MAX_ASID / (sizeof(uint32_t) * NBBY)); asid_bitmap_index++) {
		unsigned int    temp = ffs(asid_bitmap[asid_bitmap_index]);
		if (temp > 0) {
			temp -= 1;
			asid_bitmap[asid_bitmap_index] &= ~(1 << temp);
#if __ARM_KERNEL_PROTECT__
			/*
			 * We need two ASIDs: n and (n | 1).  n is used for EL0,
			 * (n | 1) for EL1.
			 */
			unsigned int temp2 = temp | 1;
			assert(temp2 < MAX_ASID);
			assert(temp2 < 32);
			assert(temp2 != temp);
			assert(asid_bitmap[asid_bitmap_index] & (1 << temp2));

			/* Grab the second ASID. */
			asid_bitmap[asid_bitmap_index] &= ~(1 << temp2);
#endif /* __ARM_KERNEL_PROTECT__ */
			pmap_simple_unlock(&pmaps_lock);

			/*
			 * We should never vend out physical ASID 0 through this
			 * method, as it belongs to the kernel.
			 */
			assert(((asid_bitmap_index * sizeof(uint32_t) * NBBY + temp) % ARM_MAX_ASID) != 0);

#if __ARM_KERNEL_PROTECT__
			/* Or the kernel EL1 ASID. */
			assert(((asid_bitmap_index * sizeof(uint32_t) * NBBY + temp) % ARM_MAX_ASID) != 1);
#endif /* __ARM_KERNEL_PROTECT__ */

			return (asid_bitmap_index * sizeof(uint32_t) * NBBY + temp);
		}
	}
	pmap_simple_unlock(&pmaps_lock);
	/*
	 * ToDo: Add code to deal with pmap with no asid panic for now. Not
	 * an issue with the small config  process hard limit
	 */
	panic("alloc_asid(): out of ASID number");
	return MAX_ASID;
}