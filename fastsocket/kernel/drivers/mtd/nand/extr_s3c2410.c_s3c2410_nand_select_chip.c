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
struct s3c2410_nand_mtd {TYPE_2__* set; struct s3c2410_nand_info* info; } ;
struct s3c2410_nand_info {unsigned long sel_bit; int /*<<< orphan*/  clk; int /*<<< orphan*/  sel_reg; TYPE_1__* platform; int /*<<< orphan*/  device; } ;
struct nand_chip {struct s3c2410_nand_mtd* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;
struct TYPE_4__ {int nr_chips; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* select_chip ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 scalar_t__ allow_clk_stop (struct s3c2410_nand_info*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_nand_select_chip(struct mtd_info *mtd, int chip)
{
	struct s3c2410_nand_info *info;
	struct s3c2410_nand_mtd *nmtd;
	struct nand_chip *this = mtd->priv;
	unsigned long cur;

	nmtd = this->priv;
	info = nmtd->info;

	if (chip != -1 && allow_clk_stop(info))
		clk_enable(info->clk);

	cur = readl(info->sel_reg);

	if (chip == -1) {
		cur |= info->sel_bit;
	} else {
		if (nmtd->set != NULL && chip > nmtd->set->nr_chips) {
			dev_err(info->device, "invalid chip %d\n", chip);
			return;
		}

		if (info->platform != NULL) {
			if (info->platform->select_chip != NULL)
				(info->platform->select_chip) (nmtd->set, chip);
		}

		cur &= ~info->sel_bit;
	}

	writel(cur, info->sel_reg);

	if (chip == -1 && allow_clk_stop(info))
		clk_disable(info->clk);
}