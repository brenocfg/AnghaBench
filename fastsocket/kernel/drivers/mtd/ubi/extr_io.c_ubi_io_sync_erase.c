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
struct ubi_device {int peb_count; scalar_t__ nor_flash; scalar_t__ ro_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int do_sync_erase (struct ubi_device*,int) ; 
 int nor_erase_prepare (struct ubi_device*,int) ; 
 int paranoid_check_not_bad (struct ubi_device*,int) ; 
 int torture_peb (struct ubi_device*,int) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (char*) ; 

int ubi_io_sync_erase(struct ubi_device *ubi, int pnum, int torture)
{
	int err, ret = 0;

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	err = paranoid_check_not_bad(ubi, pnum);
	if (err != 0)
		return err > 0 ? -EINVAL : err;

	if (ubi->ro_mode) {
		ubi_err("read-only mode");
		return -EROFS;
	}

	if (ubi->nor_flash) {
		err = nor_erase_prepare(ubi, pnum);
		if (err)
			return err;
	}

	if (torture) {
		ret = torture_peb(ubi, pnum);
		if (ret < 0)
			return ret;
	}

	err = do_sync_erase(ubi, pnum);
	if (err)
		return err;

	return ret + 1;
}