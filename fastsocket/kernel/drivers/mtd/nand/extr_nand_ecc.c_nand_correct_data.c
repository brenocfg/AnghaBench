#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {scalar_t__ priv; } ;

/* Variables and functions */
 int __nand_correct_data (unsigned char*,unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

int nand_correct_data(struct mtd_info *mtd, unsigned char *buf,
		      unsigned char *read_ecc, unsigned char *calc_ecc)
{
	return __nand_correct_data(buf, read_ecc, calc_ecc,
				   ((struct nand_chip *)mtd->priv)->ecc.size);
}