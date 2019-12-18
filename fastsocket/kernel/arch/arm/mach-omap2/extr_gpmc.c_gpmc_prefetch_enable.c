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
typedef  int uint32_t ;

/* Variables and functions */
 int CS_NUM_SHIFT ; 
 int DMA_MPU_MODE ; 
 int EBUSY ; 
 int ENABLE_PREFETCH ; 
 int /*<<< orphan*/  GPMC_PREFETCH_CONFIG1 ; 
 int /*<<< orphan*/  GPMC_PREFETCH_CONFIG2 ; 
 int /*<<< orphan*/  GPMC_PREFETCH_CONTROL ; 
 int PREFETCH_FIFOTHRESHOLD ; 
 int /*<<< orphan*/  gpmc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpmc_write_reg (int /*<<< orphan*/ ,int) ; 

int gpmc_prefetch_enable(int cs, int dma_mode,
				unsigned int u32_count, int is_write)
{
	uint32_t prefetch_config1;

	if (!(gpmc_read_reg(GPMC_PREFETCH_CONTROL))) {
		/* Set the amount of bytes to be prefetched */
		gpmc_write_reg(GPMC_PREFETCH_CONFIG2, u32_count);

		/* Set dma/mpu mode, the prefetch read / post write and
		 * enable the engine. Set which cs is has requested for.
		 */
		prefetch_config1 = ((cs << CS_NUM_SHIFT) |
					PREFETCH_FIFOTHRESHOLD |
					ENABLE_PREFETCH |
					(dma_mode << DMA_MPU_MODE) |
					(0x1 & is_write));
		gpmc_write_reg(GPMC_PREFETCH_CONFIG1, prefetch_config1);
	} else {
		return -EBUSY;
	}
	/*  Start the prefetch engine */
	gpmc_write_reg(GPMC_PREFETCH_CONTROL, 0x1);

	return 0;
}