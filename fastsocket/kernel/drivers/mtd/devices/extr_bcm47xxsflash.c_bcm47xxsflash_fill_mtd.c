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
struct mtd_info {char* name; int writebufsize; int writesize; int /*<<< orphan*/  flags; int /*<<< orphan*/  _read; int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; struct bcm47xxsflash* priv; } ;
struct bcm47xxsflash {int /*<<< orphan*/  size; struct mtd_info mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_CAP_ROM ; 
 int /*<<< orphan*/  MTD_ROM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bcm47xxsflash_read ; 

__attribute__((used)) static void bcm47xxsflash_fill_mtd(struct bcm47xxsflash *b47s)
{
	struct mtd_info *mtd = &b47s->mtd;

	mtd->priv = b47s;
	mtd->name = "bcm47xxsflash";
	mtd->owner = THIS_MODULE;
	mtd->type = MTD_ROM;
	mtd->size = b47s->size;
	mtd->_read = bcm47xxsflash_read;

	/* TODO: implement writing support and verify/change following code */
	mtd->flags = MTD_CAP_ROM;
	mtd->writebufsize = mtd->writesize = 1;
}