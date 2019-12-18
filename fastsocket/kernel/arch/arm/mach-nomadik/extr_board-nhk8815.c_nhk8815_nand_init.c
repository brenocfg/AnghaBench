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
 int /*<<< orphan*/  FSMC_PATT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSMC_PCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSMC_PMEM (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nhk8815_nand_init(void)
{
	/* FSMC setup for nand chip select (8-bit nand in 8815NHK) */
	writel(0x0000000E, FSMC_PCR(0));
	writel(0x000D0A00, FSMC_PMEM(0));
	writel(0x00100A00, FSMC_PATT(0));

	/* enable access to the chip select area */
	writel(readl(FSMC_PCR(0)) | 0x04, FSMC_PCR(0));

	return 0;
}