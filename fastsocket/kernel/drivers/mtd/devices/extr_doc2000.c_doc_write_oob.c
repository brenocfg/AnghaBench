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
struct mtd_oob_ops {scalar_t__ mode; int /*<<< orphan*/  oobbuf; int /*<<< orphan*/  retlen; int /*<<< orphan*/  len; scalar_t__ ooboffs; } ;
struct mtd_info {struct DiskOnChip* priv; } ;
struct DiskOnChip {int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MTD_OOB_PLACE ; 
 int doc_write_oob_nolock (struct mtd_info*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int doc_write_oob(struct mtd_info *mtd, loff_t ofs,
			 struct mtd_oob_ops *ops)
{
	struct DiskOnChip *this = mtd->priv;
	int ret;

	BUG_ON(ops->mode != MTD_OOB_PLACE);

	mutex_lock(&this->lock);
	ret = doc_write_oob_nolock(mtd, ofs + ops->ooboffs, ops->len,
				   &ops->retlen, ops->oobbuf);

	mutex_unlock(&this->lock);
	return ret;
}