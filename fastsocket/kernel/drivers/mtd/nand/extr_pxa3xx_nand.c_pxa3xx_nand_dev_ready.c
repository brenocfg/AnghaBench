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
struct pxa3xx_nand_info {int dummy; } ;
struct mtd_info {struct pxa3xx_nand_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDSR ; 
 int NDSR_RDY ; 
 int nand_readl (struct pxa3xx_nand_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa3xx_nand_dev_ready(struct mtd_info *mtd)
{
	struct pxa3xx_nand_info *info = mtd->priv;
	return (nand_readl(info, NDSR) & NDSR_RDY) ? 1 : 0;
}