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
struct nand_chip {int options; int /*<<< orphan*/  buffers; int /*<<< orphan*/  bbt; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int NAND_OWN_BUFFERS ; 
 int /*<<< orphan*/  del_mtd_device (struct mtd_info*) ; 
 int /*<<< orphan*/  del_mtd_partitions (struct mtd_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void nand_release(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

#ifdef CONFIG_MTD_PARTITIONS
	/* Deregister partitions */
	del_mtd_partitions(mtd);
#endif
	/* Deregister the device */
	del_mtd_device(mtd);

	/* Free bad block table memory */
	kfree(chip->bbt);
	if (!(chip->options & NAND_OWN_BUFFERS))
		kfree(chip->buffers);
}