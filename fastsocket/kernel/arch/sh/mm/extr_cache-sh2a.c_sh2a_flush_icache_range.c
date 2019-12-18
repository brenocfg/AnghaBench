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
struct flusher_data {int addr1; int addr2; } ;

/* Variables and functions */
 unsigned long CACHE_IC_ADDRESS_ARRAY ; 
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 unsigned long CACHE_PHYSADDR_MASK ; 
 int L1_CACHE_BYTES ; 
 unsigned long SH_CACHE_UPDATED ; 
 int /*<<< orphan*/  back_to_cached () ; 
 unsigned long ctrl_inl (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void sh2a_flush_icache_range(void *args)
{
	struct flusher_data *data = args;
	unsigned long start, end;
	unsigned long v;
	unsigned long flags;

	start = data->addr1 & ~(L1_CACHE_BYTES-1);
	end = (data->addr2 + L1_CACHE_BYTES-1) & ~(L1_CACHE_BYTES-1);

	local_irq_save(flags);
	jump_to_uncached();

	for (v = start; v < end; v+=L1_CACHE_BYTES) {
		unsigned long addr = (v & 0x000007f0);
		int way;
		/* O-Cache writeback */
		for (way = 0; way < 4; way++) {
			unsigned long data =  ctrl_inl(CACHE_OC_ADDRESS_ARRAY | addr | (way << 11));
			if ((data & CACHE_PHYSADDR_MASK) == (v & CACHE_PHYSADDR_MASK)) {
				data &= ~SH_CACHE_UPDATED;
				ctrl_outl(data, CACHE_OC_ADDRESS_ARRAY | addr | (way << 11));
			}
		}
		/* I-Cache invalidate */
		ctrl_outl(addr,
			  CACHE_IC_ADDRESS_ARRAY | addr | 0x00000008);
	}

	back_to_cached();
	local_irq_restore(flags);
}