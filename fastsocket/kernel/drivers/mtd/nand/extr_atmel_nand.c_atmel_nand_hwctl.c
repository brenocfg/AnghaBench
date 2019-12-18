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
struct nand_chip {struct atmel_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;
struct atmel_nand_host {int /*<<< orphan*/  ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_ECC_RST ; 
 int /*<<< orphan*/  CR ; 
 scalar_t__ cpu_is_at32ap7000 () ; 
 int /*<<< orphan*/  ecc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_nand_hwctl(struct mtd_info *mtd, int mode)
{
	if (cpu_is_at32ap7000()) {
		struct nand_chip *nand_chip = mtd->priv;
		struct atmel_nand_host *host = nand_chip->priv;
		ecc_writel(host->ecc, CR, ATMEL_ECC_RST);
	}
}