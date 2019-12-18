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
struct pxa3xx_nand_timing {int /*<<< orphan*/  tAR; int /*<<< orphan*/  tWHR; int /*<<< orphan*/  tR; int /*<<< orphan*/  tRP; int /*<<< orphan*/  tRH; int /*<<< orphan*/  tWP; int /*<<< orphan*/  tWH; int /*<<< orphan*/  tCS; int /*<<< orphan*/  tCH; } ;
struct pxa3xx_nand_info {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDTR0CS0 ; 
 int NDTR0_tCH (int /*<<< orphan*/ ) ; 
 int NDTR0_tCS (int /*<<< orphan*/ ) ; 
 int NDTR0_tRH (int /*<<< orphan*/ ) ; 
 int NDTR0_tRP (int /*<<< orphan*/ ) ; 
 int NDTR0_tWH (int /*<<< orphan*/ ) ; 
 int NDTR0_tWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDTR1CS0 ; 
 int NDTR1_tAR (int /*<<< orphan*/ ) ; 
 int NDTR1_tR (int /*<<< orphan*/ ) ; 
 int NDTR1_tWHR (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_writel (struct pxa3xx_nand_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns2cycle (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pxa3xx_nand_set_timing(struct pxa3xx_nand_info *info,
				   const struct pxa3xx_nand_timing *t)
{
	unsigned long nand_clk = clk_get_rate(info->clk);
	uint32_t ndtr0, ndtr1;

	ndtr0 = NDTR0_tCH(ns2cycle(t->tCH, nand_clk)) |
		NDTR0_tCS(ns2cycle(t->tCS, nand_clk)) |
		NDTR0_tWH(ns2cycle(t->tWH, nand_clk)) |
		NDTR0_tWP(ns2cycle(t->tWP, nand_clk)) |
		NDTR0_tRH(ns2cycle(t->tRH, nand_clk)) |
		NDTR0_tRP(ns2cycle(t->tRP, nand_clk));

	ndtr1 = NDTR1_tR(ns2cycle(t->tR, nand_clk)) |
		NDTR1_tWHR(ns2cycle(t->tWHR, nand_clk)) |
		NDTR1_tAR(ns2cycle(t->tAR, nand_clk));

	nand_writel(info, NDTR0CS0, ndtr0);
	nand_writel(info, NDTR1CS0, ndtr1);
}