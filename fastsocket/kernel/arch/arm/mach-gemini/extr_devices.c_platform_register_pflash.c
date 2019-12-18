#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtd_partition {int dummy; } ;
struct TYPE_4__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_3__ {int width; unsigned int nr_parts; struct mtd_partition* parts; } ;

/* Variables and functions */
 int ENXIO ; 
 unsigned int FLASH_TYPE_MASK ; 
 unsigned int FLASH_TYPE_PARALLEL ; 
 unsigned int FLASH_WIDTH_16BIT ; 
 int /*<<< orphan*/  GEMINI_GLOBAL_BASE ; 
 scalar_t__ GLOBAL_MISC_CTRL ; 
 scalar_t__ GLOBAL_STATUS ; 
 scalar_t__ IO_ADDRESS (int /*<<< orphan*/ ) ; 
 unsigned int NAND_PADS_DISABLE ; 
 unsigned int PFLASH_PADS_DISABLE ; 
 unsigned int SFLASH_PADS_DISABLE ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 TYPE_2__ flash_resource ; 
 int /*<<< orphan*/  pflash_device ; 
 TYPE_1__ pflash_platform_data ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 

int platform_register_pflash(unsigned int size, struct mtd_partition *parts,
			     unsigned int nr_parts)
{
	unsigned int reg;

	reg = __raw_readl(IO_ADDRESS(GEMINI_GLOBAL_BASE) + GLOBAL_STATUS);

	if ((reg & FLASH_TYPE_MASK) != FLASH_TYPE_PARALLEL)
		return -ENXIO;

	if (reg & FLASH_WIDTH_16BIT)
		pflash_platform_data.width = 2;
	else
		pflash_platform_data.width = 1;

	/* enable parallel flash pins and disable others */
	reg = __raw_readl(IO_ADDRESS(GEMINI_GLOBAL_BASE) + GLOBAL_MISC_CTRL);
	reg &= ~PFLASH_PADS_DISABLE;
	reg |= SFLASH_PADS_DISABLE | NAND_PADS_DISABLE;
	__raw_writel(reg, IO_ADDRESS(GEMINI_GLOBAL_BASE) + GLOBAL_MISC_CTRL);

	flash_resource.end = flash_resource.start + size - 1;

	pflash_platform_data.parts = parts;
	pflash_platform_data.nr_parts = nr_parts;

	return platform_device_register(&pflash_device);
}