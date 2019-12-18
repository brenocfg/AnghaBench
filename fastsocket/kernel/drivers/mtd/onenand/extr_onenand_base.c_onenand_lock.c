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
typedef  int /*<<< orphan*/  uint64_t ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FL_LOCKING ; 
 int /*<<< orphan*/  ONENAND_CMD_LOCK ; 
 int onenand_do_lock_cmd (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_release_device (struct mtd_info*) ; 

__attribute__((used)) static int onenand_lock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	int ret;

	onenand_get_device(mtd, FL_LOCKING);
	ret = onenand_do_lock_cmd(mtd, ofs, len, ONENAND_CMD_LOCK);
	onenand_release_device(mtd);
	return ret;
}