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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  mmr ;

/* Variables and functions */
#define  BFIN_MEM_ACCESS_CORE 131 
#define  BFIN_MEM_ACCESS_CORE_ONLY 130 
#define  BFIN_MEM_ACCESS_DMA 129 
#define  BFIN_MEM_ACCESS_ITEST 128 
 int EFAULT ; 
 unsigned long SYSMMR_BASE ; 
 int /*<<< orphan*/  bfin_read16 (char*) ; 
 int /*<<< orphan*/  bfin_read32 (char*) ; 
 int /*<<< orphan*/  dma_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  isram_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int probe_kernel_read (char*,char*,int) ; 
 int validate_memory_access_address (unsigned long,int) ; 

__attribute__((used)) static int bfin_probe_kernel_read(char *dst, char *src, int size)
{
	unsigned long lsrc = (unsigned long)src;
	int mem_type;

	mem_type = validate_memory_access_address(lsrc, size);
	if (mem_type < 0)
		return mem_type;

	if (lsrc >= SYSMMR_BASE) {
		if (size == 2 && lsrc % 2 == 0) {
			u16 mmr = bfin_read16(src);
			memcpy(dst, &mmr, sizeof(mmr));
			return 0;
		} else if (size == 4 && lsrc % 4 == 0) {
			u32 mmr = bfin_read32(src);
			memcpy(dst, &mmr, sizeof(mmr));
			return 0;
		}
	} else {
		switch (mem_type) {
			case BFIN_MEM_ACCESS_CORE:
			case BFIN_MEM_ACCESS_CORE_ONLY:
				return probe_kernel_read(dst, src, size);
			/* XXX: should support IDMA here with SMP */
			case BFIN_MEM_ACCESS_DMA:
				if (dma_memcpy(dst, src, size))
					return 0;
				break;
			case BFIN_MEM_ACCESS_ITEST:
				if (isram_memcpy(dst, src, size))
					return 0;
				break;
		}
	}

	return -EFAULT;
}