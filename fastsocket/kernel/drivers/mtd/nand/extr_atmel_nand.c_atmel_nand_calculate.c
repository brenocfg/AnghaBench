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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {TYPE_1__* layout; } ;
struct nand_chip {TYPE_2__ ecc; struct atmel_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;
struct atmel_nand_host {int /*<<< orphan*/  ecc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * eccpos; } ;

/* Variables and functions */
 unsigned int ATMEL_ECC_NPARITY ; 
 int /*<<< orphan*/  NPR ; 
 int /*<<< orphan*/  PR ; 
 unsigned int ecc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_calculate(struct mtd_info *mtd,
		const u_char *dat, unsigned char *ecc_code)
{
	struct nand_chip *nand_chip = mtd->priv;
	struct atmel_nand_host *host = nand_chip->priv;
	uint32_t *eccpos = nand_chip->ecc.layout->eccpos;
	unsigned int ecc_value;

	/* get the first 2 ECC bytes */
	ecc_value = ecc_readl(host->ecc, PR);

	ecc_code[0] = ecc_value & 0xFF;
	ecc_code[1] = (ecc_value >> 8) & 0xFF;

	/* get the last 2 ECC bytes */
	ecc_value = ecc_readl(host->ecc, NPR) & ATMEL_ECC_NPARITY;

	ecc_code[2] = ecc_value & 0xFF;
	ecc_code[3] = (ecc_value >> 8) & 0xFF;

	return 0;
}