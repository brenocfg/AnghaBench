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
struct onenand_chip {struct bbm_info* bbm; } ;
struct mtd_info {struct onenand_chip* priv; } ;
struct bbm_info {int (* isbad_bbt ) (struct mtd_info*,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int onenand_block_isbad_nolock(struct mtd_info *mtd, loff_t ofs, int allowbbt)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm = this->bbm;

	/* Return info from the table */
	return bbm->isbad_bbt(mtd, ofs, allowbbt);
}