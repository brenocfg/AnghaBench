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
struct mtd_info {struct cafe_priv* priv; } ;
struct cafe_priv {int /*<<< orphan*/  ctl1; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL1_CHIPSELECT ; 
 int /*<<< orphan*/  cafe_dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void cafe_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct cafe_priv *cafe = mtd->priv;

	cafe_dev_dbg(&cafe->pdev->dev, "select_chip %d\n", chipnr);

	/* Mask the appropriate bit into the stored value of ctl1
	   which will be used by cafe_nand_cmdfunc() */
	if (chipnr)
		cafe->ctl1 |= CTRL1_CHIPSELECT;
	else
		cafe->ctl1 &= ~CTRL1_CHIPSELECT;
}