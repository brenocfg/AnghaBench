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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_oob_ops {size_t len; size_t retlen; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/  ooblen; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FL_WRITING ; 
 int /*<<< orphan*/  onenand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_release_device (struct mtd_info*) ; 
 int onenand_write_ops_nolock (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int onenand_write(struct mtd_info *mtd, loff_t to, size_t len,
	size_t *retlen, const u_char *buf)
{
	struct mtd_oob_ops ops = {
		.len	= len,
		.ooblen	= 0,
		.datbuf	= (u_char *) buf,
		.oobbuf	= NULL,
	};
	int ret;

	onenand_get_device(mtd, FL_WRITING);
	ret = onenand_write_ops_nolock(mtd, to, &ops);
	onenand_release_device(mtd);

	*retlen = ops.retlen;
	return ret;
}