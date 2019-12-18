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
struct onenand_chip {int dummy; } ;
struct mtd_oob_ops {int mode; scalar_t__ datbuf; } ;
struct mtd_info {struct onenand_chip* priv; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FL_READING ; 
#define  MTD_OOB_AUTO 130 
#define  MTD_OOB_PLACE 129 
#define  MTD_OOB_RAW 128 
 scalar_t__ ONENAND_IS_MLC (struct onenand_chip*) ; 
 int /*<<< orphan*/  onenand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int onenand_mlc_read_ops_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int onenand_read_oob_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int onenand_read_ops_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int /*<<< orphan*/  onenand_release_device (struct mtd_info*) ; 

__attribute__((used)) static int onenand_read_oob(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	struct onenand_chip *this = mtd->priv;
	int ret;

	switch (ops->mode) {
	case MTD_OOB_PLACE:
	case MTD_OOB_AUTO:
		break;
	case MTD_OOB_RAW:
		/* Not implemented yet */
	default:
		return -EINVAL;
	}

	onenand_get_device(mtd, FL_READING);
	if (ops->datbuf)
		ret = ONENAND_IS_MLC(this) ?
			onenand_mlc_read_ops_nolock(mtd, from, ops) :
			onenand_read_ops_nolock(mtd, from, ops);
	else
		ret = onenand_read_oob_nolock(mtd, from, ops);
	onenand_release_device(mtd);

	return ret;
}