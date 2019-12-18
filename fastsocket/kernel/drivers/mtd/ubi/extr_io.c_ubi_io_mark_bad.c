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
struct ubi_device {int peb_count; int peb_size; int /*<<< orphan*/  bad_allowed; scalar_t__ ro_mode; struct mtd_info* mtd; } ;
struct mtd_info {int (* block_markbad ) (struct mtd_info*,int) ;} ;
typedef  int loff_t ;

/* Variables and functions */
 int EROFS ; 
 int stub1 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (char*,...) ; 

int ubi_io_mark_bad(const struct ubi_device *ubi, int pnum)
{
	int err;
	struct mtd_info *mtd = ubi->mtd;

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->ro_mode) {
		ubi_err("read-only mode");
		return -EROFS;
	}

	if (!ubi->bad_allowed)
		return 0;

	err = mtd->block_markbad(mtd, (loff_t)pnum * ubi->peb_size);
	if (err)
		ubi_err("cannot mark PEB %d bad, error %d", pnum, err);
	return err;
}