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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_bbt_descr {int dummy; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ check_pattern (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nand_bbt_descr*) ; 
 int scan_read_raw (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int scan_block_full(struct mtd_info *mtd, struct nand_bbt_descr *bd,
			   loff_t offs, uint8_t *buf, size_t readlen,
			   int scanlen, int len)
{
	int ret, j;

	ret = scan_read_raw(mtd, buf, offs, readlen);
	if (ret)
		return ret;

	for (j = 0; j < len; j++, buf += scanlen) {
		if (check_pattern(buf, scanlen, mtd->writesize, bd))
			return 1;
	}
	return 0;
}