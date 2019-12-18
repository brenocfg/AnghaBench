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
 unsigned short RD_RDY ; 
 int /*<<< orphan*/  SSYNC () ; 
 int WB_FULL ; 
 unsigned short bfin_read_NFC_IRQSTAT () ; 
 int /*<<< orphan*/  bfin_read_NFC_READ () ; 
 int bfin_read_NFC_STAT () ; 
 int /*<<< orphan*/  bfin_write_NFC_DATA_RD (int) ; 
 int /*<<< orphan*/  bfin_write_NFC_IRQSTAT (unsigned short) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void bf5xx_nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i;
	unsigned short val;

	/*
	 * Data reads are requested by first writing to NFC_DATA_RD
	 * and then reading back from NFC_READ.
	 */
	for (i = 0; i < len; i++) {
		while (bfin_read_NFC_STAT() & WB_FULL)
			cpu_relax();

		/* Contents do not matter */
		bfin_write_NFC_DATA_RD(0x0000);
		SSYNC();

		while ((bfin_read_NFC_IRQSTAT() & RD_RDY) != RD_RDY)
			cpu_relax();

		buf[i] = bfin_read_NFC_READ();

		val = bfin_read_NFC_IRQSTAT();
		val |= RD_RDY;
		bfin_write_NFC_IRQSTAT(val);
		SSYNC();
	}
}