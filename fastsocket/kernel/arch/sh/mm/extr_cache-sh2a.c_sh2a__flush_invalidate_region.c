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
 unsigned long CACHE_IC_ADDRESS_ARRAY ; 
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 unsigned long CACHE_PHYSADDR_MASK ; 
 unsigned long CCR ; 
 unsigned long CCR_OCACHE_INVALIDATE ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  back_to_cached () ; 
 unsigned long ctrl_inl (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void sh2a__flush_invalidate_region(void *start, int size)
{
	unsigned long v;
	unsigned long begin, end;
	unsigned long flags;

	begin = (unsigned long)start & ~(L1_CACHE_BYTES-1);
	end = ((unsigned long)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	local_irq_save(flags);
	jump_to_uncached();

#ifdef CONFIG_CACHE_WRITEBACK
	ctrl_outl(ctrl_inl(CCR) | CCR_OCACHE_INVALIDATE, CCR);
	/* I-cache invalidate */
	for (v = begin; v < end; v+=L1_CACHE_BYTES) {
		ctrl_outl((v & CACHE_PHYSADDR_MASK),
			  CACHE_IC_ADDRESS_ARRAY | (v & 0x000007f0) | 0x00000008);
	}
#else
	for (v = begin; v < end; v+=L1_CACHE_BYTES) {
		ctrl_outl((v & CACHE_PHYSADDR_MASK),
			  CACHE_IC_ADDRESS_ARRAY | (v & 0x000007f0) | 0x00000008);
		ctrl_outl((v & CACHE_PHYSADDR_MASK),
			  CACHE_OC_ADDRESS_ARRAY | (v & 0x000007f0) | 0x00000008);
	}
#endif
	back_to_cached();
	local_irq_restore(flags);
}