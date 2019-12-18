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
struct onenand_chip {int options; struct bbm_info* oob_buf; struct bbm_info* page_buf; struct bbm_info* bbm; } ;
struct mtd_info {struct bbm_info* eraseregions; struct onenand_chip* priv; } ;
struct bbm_info {struct bbm_info* bbt; } ;

/* Variables and functions */
 int ONENAND_OOBBUF_ALLOC ; 
 int ONENAND_PAGEBUF_ALLOC ; 
 int /*<<< orphan*/  del_mtd_device (struct mtd_info*) ; 
 int /*<<< orphan*/  del_mtd_partitions (struct mtd_info*) ; 
 int /*<<< orphan*/  kfree (struct bbm_info*) ; 

void onenand_release(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;

#ifdef CONFIG_MTD_PARTITIONS
	/* Deregister partitions */
	del_mtd_partitions (mtd);
#endif
	/* Deregister the device */
	del_mtd_device (mtd);

	/* Free bad block table memory, if allocated */
	if (this->bbm) {
		struct bbm_info *bbm = this->bbm;
		kfree(bbm->bbt);
		kfree(this->bbm);
	}
	/* Buffers allocated by onenand_scan */
	if (this->options & ONENAND_PAGEBUF_ALLOC)
		kfree(this->page_buf);
	if (this->options & ONENAND_OOBBUF_ALLOC)
		kfree(this->oob_buf);
	kfree(mtd->eraseregions);
}