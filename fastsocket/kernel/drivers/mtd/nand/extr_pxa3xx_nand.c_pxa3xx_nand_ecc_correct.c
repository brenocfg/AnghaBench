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
typedef  int /*<<< orphan*/  uint8_t ;
struct pxa3xx_nand_info {scalar_t__ retcode; } ;
struct mtd_info {struct pxa3xx_nand_info* priv; } ;

/* Variables and functions */
 scalar_t__ ERR_NONE ; 
 scalar_t__ ERR_SBERR ; 

__attribute__((used)) static int pxa3xx_nand_ecc_correct(struct mtd_info *mtd,
		uint8_t *dat, uint8_t *read_ecc, uint8_t *calc_ecc)
{
	struct pxa3xx_nand_info *info = mtd->priv;
	/*
	 * Any error include ERR_SEND_CMD, ERR_DBERR, ERR_BUSERR, we
	 * consider it as a ecc error which will tell the caller the
	 * read fail We have distinguish all the errors, but the
	 * nand_read_ecc only check this function return value
	 *
	 * Corrected (single-bit) errors must also be noted.
	 */
	if (info->retcode == ERR_SBERR)
		return 1;
	else if (info->retcode != ERR_NONE)
		return -1;

	return 0;
}