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
struct pxa3xx_nand_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDCR ; 
 int nand_readl (struct pxa3xx_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_writel (struct pxa3xx_nand_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_int(struct pxa3xx_nand_info *info, uint32_t int_mask)
{
	uint32_t ndcr;

	ndcr = nand_readl(info, NDCR);
	nand_writel(info, NDCR, ndcr | int_mask);
}