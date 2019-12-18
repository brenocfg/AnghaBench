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
struct mtd_info {struct block2mtd_dev* priv; } ;
struct erase_info {size_t addr; size_t len; void* state; } ;
struct block2mtd_dev {int /*<<< orphan*/  write_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int) ; 
 void* MTD_ERASE_DONE ; 
 void* MTD_ERASE_FAILED ; 
 void* MTD_ERASING ; 
 int _block2mtd_erase (struct block2mtd_dev*,size_t,size_t) ; 
 int /*<<< orphan*/  mtd_erase_callback (struct erase_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int block2mtd_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct block2mtd_dev *dev = mtd->priv;
	size_t from = instr->addr;
	size_t len = instr->len;
	int err;

	instr->state = MTD_ERASING;
	mutex_lock(&dev->write_mutex);
	err = _block2mtd_erase(dev, from, len);
	mutex_unlock(&dev->write_mutex);
	if (err) {
		ERROR("erase failed err = %d", err);
		instr->state = MTD_ERASE_FAILED;
	} else
		instr->state = MTD_ERASE_DONE;

	instr->state = MTD_ERASE_DONE;
	mtd_erase_callback(instr);
	return err;
}