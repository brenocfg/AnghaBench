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
struct mtd_info {scalar_t__ size; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FL_READING ; 
 int onenand_block_isbad_nolock (struct mtd_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_release_device (struct mtd_info*) ; 

__attribute__((used)) static int onenand_block_isbad(struct mtd_info *mtd, loff_t ofs)
{
	int ret;

	/* Check for invalid offset */
	if (ofs > mtd->size)
		return -EINVAL;

	onenand_get_device(mtd, FL_READING);
	ret = onenand_block_isbad_nolock(mtd, ofs, 0);
	onenand_release_device(mtd);
	return ret;
}