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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSYNC () ; 
 int WB_FULL ; 
 int bfin_read_NFC_STAT () ; 
 int /*<<< orphan*/  bfin_write_NFC_DATA_WR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void bf5xx_nand_write_buf(struct mtd_info *mtd,
				const uint8_t *buf, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		while (bfin_read_NFC_STAT() & WB_FULL)
			cpu_relax();

		bfin_write_NFC_DATA_WR(buf[i]);
		SSYNC();
	}
}