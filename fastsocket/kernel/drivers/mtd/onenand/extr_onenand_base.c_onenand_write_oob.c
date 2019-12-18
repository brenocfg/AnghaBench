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
struct mtd_oob_ops {int mode; scalar_t__ datbuf; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FL_WRITING ; 
#define  MTD_OOB_AUTO 130 
#define  MTD_OOB_PLACE 129 
#define  MTD_OOB_RAW 128 
 int /*<<< orphan*/  onenand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_release_device (struct mtd_info*) ; 
 int onenand_write_oob_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int onenand_write_ops_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int onenand_write_oob(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
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

	onenand_get_device(mtd, FL_WRITING);
	if (ops->datbuf)
		ret = onenand_write_ops_nolock(mtd, to, ops);
	else
		ret = onenand_write_oob_nolock(mtd, to, ops);
	onenand_release_device(mtd);

	return ret;
}