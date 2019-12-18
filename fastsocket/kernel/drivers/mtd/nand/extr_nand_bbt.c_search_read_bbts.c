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
struct nand_bbt_descr {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  search_bbt (struct mtd_info*,int /*<<< orphan*/ *,struct nand_bbt_descr*) ; 

__attribute__((used)) static int search_read_bbts(struct mtd_info *mtd, uint8_t * buf, struct nand_bbt_descr *td, struct nand_bbt_descr *md)
{
	/* Search the primary table */
	search_bbt(mtd, buf, td);

	/* Search the mirror table */
	if (md)
		search_bbt(mtd, buf, md);

	/* Force result check */
	return 1;
}