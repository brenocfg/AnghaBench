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
struct pxa3xx_nand_timing {void* tAR; void* tWHR; void* tR; void* tRP; void* tRH; void* tWP; void* tWH; void* tCS; void* tCH; } ;
struct pxa3xx_nand_info {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDTR0CS0 ; 
 int /*<<< orphan*/  NDTR1CS0 ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 void* cycle2ns (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nand_readl (struct pxa3xx_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tAR_NDTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tCH_NDTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tCS_NDTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tRH_NDTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tRP_NDTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tR_NDTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tWHR_NDTR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tWH_NDTR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tWP_NDTR0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa3xx_nand_detect_timing(struct pxa3xx_nand_info *info,
				      struct pxa3xx_nand_timing *t)
{
	unsigned long nand_clk = clk_get_rate(info->clk);
	uint32_t ndtr0 = nand_readl(info, NDTR0CS0);
	uint32_t ndtr1 = nand_readl(info, NDTR1CS0);

	t->tCH = cycle2ns(tCH_NDTR0(ndtr0), nand_clk);
	t->tCS = cycle2ns(tCS_NDTR0(ndtr0), nand_clk);
	t->tWH = cycle2ns(tWH_NDTR0(ndtr0), nand_clk);
	t->tWP = cycle2ns(tWP_NDTR0(ndtr0), nand_clk);
	t->tRH = cycle2ns(tRH_NDTR0(ndtr0), nand_clk);
	t->tRP = cycle2ns(tRP_NDTR0(ndtr0), nand_clk);

	t->tR = cycle2ns(tR_NDTR1(ndtr1), nand_clk);
	t->tWHR = cycle2ns(tWHR_NDTR1(ndtr1), nand_clk);
	t->tAR = cycle2ns(tAR_NDTR1(ndtr1), nand_clk);
}