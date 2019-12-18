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
 int /*<<< orphan*/  bfin_write16 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write32 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  isram_memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int probe_kernel_write (char*,char*,int) ; 
 int validate_memory_access_address (unsigned long,int) ; 

__attribute__((used)) static int bfin_probe_kernel_write(char *dst, char *src, int size)
{
	unsigned long ldst = (unsigned long)dst;
	int mem_type;

	mem_type = validate_memory_access_address(ldst, size);
	if (mem_type < 0)
		return mem_type;

	if (ldst >= SYSMMR_BASE) {
		if (size == 2 && ldst % 2 == 0) {
			u16 mmr;
			memcpy(&mmr, src, sizeof(mmr));
			bfin_write16(dst, mmr);
			return 0;
		} else if (size == 4 && ldst % 4 == 0) {
			u32 mmr;
			memcpy(&mmr, src, sizeof(mmr));
			bfin_write32(dst, mmr);
			return 0;
		}
	} else {
		switch (mem_type) {
			case BFIN_MEM_ACCESS_CORE:
			case BFIN_MEM_ACCESS_CORE_ONLY:
				return probe_kernel_write(dst, src, size);
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